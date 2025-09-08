#ifndef TIFALIBS_MATH_MPI
#define TIFALIBS_MATH_MPI

#include "../conv/conv_u128.hpp"
#include "../fast/str2uint_si64.hpp"
#include "../util/strip.hpp"
#include "../util/traits_others.hpp"

namespace tifa_libs::math {

struct mpi : vecu {
  static CEXP u32 D = 1e8, lgD = 8, sqrtD = 1e4;
  static_assert(sqrtD * sqrtD == D);

 private:
  struct ict4 {
    CEXP static auto num = [] {
      arr<u32, sqrtD> num;
      for (u32 e0 = (48 << 0), j = 0; e0 < (58 << 0); e0 += (1 << 0))
        for (u32 e1 = (48 << 8); e1 < (58 << 8); e1 += (1 << 8))
          for (u32 e2 = (48 << 16); e2 < (58 << 16); e2 += (1 << 16))
            for (u32 e3 = (48 << 24); e3 < (58 << 24); e3 += (1 << 24)) num[j++] = e0 ^ e1 ^ e2 ^ e3;
      return num;
    }();
    static auto get(u32 x) NE { return (const char*)(num.data() + x); }
  };

  bool neg;

#define vec_like std::derived_from<vecu> auto
  // name starts with u  ==>  ignore sign
  static CEXP auto ucmp(vec_like CR a, vec_like CR b) NE {
    if (a.size() != b.size()) return a.size() <=> b.size();
    return std::lexicographical_compare_three_way(a.rbegin(), a.rend(), b.rbegin(), b.rend());
  }
  static CEXP auto cmp(mpi CR a, mpi CR b) NE {
    if (a.neg) {
      retif_((b.neg), ucmp(b, a), std::strong_ordering::less);
    } else retif_((b.neg), std::strong_ordering::greater, ucmp(a, b));
  }
  static CEXP bool is_0(vec_like CR a) NE { return a.empty(); }
  static CEXP bool is_pm1(vec_like CR a) NE { return a.size() == 1 && a[0] == 1; }
  static CEXP bool is_1(mpi CR a) NE { return !a.neg && is_pm1(a); }
  static CEXP void shrink_(vec_like& a) NE {
    auto [_, r] = rstrip_view(a, [](u32 x) { return !x; });
    a.erase(r, a.end());
  }
  template <int_c T>
  static CEXP vecu int2vecu(T x) NE {
    if CEXP (sint_c<T>) assert(x >= 0);
    vecu res;
    while (x) res.push_back((u32)(x % D)), x /= D;
    return res;
  }
  static CEXP i64 uvec2i64(vec_like CR a) NE {
    i64 res = 0;
    for (u32 i = (u32)a.size() - 1; ~i; --i) res = res * D + a[i];
    return res;
  }

 public:
  CEXP mpi() NE = default;
  CEXP mpi(bool n, itlu x) NE : vecu(x), neg(n) {}
  CEXP mpi(bool n, spnu d) NE : vecu(d.begin(), d.end()), neg(n) {}
  template <int_c T>
  CEXP mpi(T x) NE : mpi() {
    if CEXP (sint_c<T>)
      if (x < 0) neg = true, x = -x;
    while (x) push_back(u32(to_uint_t<T>(x) % D)), x /= (T)D;
  }
  CEXP mpi(strn s) NE : mpi() {
    if (assert(!s.empty()); s.size() == 1u) {
      if (s[0] == '0') return;
      assert(isdigit(s[0])), push_back(s[0] & 15);
      return;
    }
    u32 l = 0;
    if (s[0] == '-') ++l, neg = true;
    u32 _ = 0;
    if (u32 ofs = u32(s.size() - l) & 7; ofs) {
      flt_ (u32, i, l, l + ofs) _ = _ * 10 + (s[i] & 15);
      l += ofs;
    }
    if (l) s = s.substr(l);
    for (u32 ie = (u32)s.size(); ie >= lgD; ie -= lgD)
      push_back(str2uint_si64(s.data() + ie - lgD));
    if (_) push_back(_);
  }

  CEXP void set_neg(bool s) NE { neg = s; }
  CEXP bool is_neg() CNE { return neg; }
  CEXP bool is_zero() CNE { return is_0(*this); }
  CEXP void shrink() NE { shrink_(*this); }
  friend CEXP mpi abs(mpi m) NE {
    m.neg = false;
    return m;
  }

  friend CEXP mpi operator+(mpi CR l, mpi CR r) NE {
    if (l.neg == r.neg) return {l.neg, uadd(l, r)};
    if (std::is_lteq(ucmp(l, r))) {
      auto c = usub(r, l);
      return {is_0(c) ? false : r.neg, c};
    }
    auto c = usub(l, r);
    return {is_0(c) ? false : l.neg, c};
  }
  friend CEXP mpi operator-(mpi CR l, mpi CR r) NE { return l + (-r); }
  friend CEXP mpi operator*(mpi CR l, mpi CR r) NE {
    auto c = umul(l, r);
    bool n = is_0(c) ? false : (l.neg ^ r.neg);
    return {n, c};
  }
  friend CEXP ptt<mpi> divmod(mpi CR l, mpi CR r) NE {
    auto dm = udivmod(l, r);
    return {mpi{is_0(dm.first) ? false : l.neg != r.neg, dm.first}, mpi{is_0(dm.second) ? false : l.neg, dm.second}};
  }
  friend CEXP mpi operator/(mpi CR l, mpi CR r) NE { return divmod(l, r).first; }
  friend CEXP mpi operator%(mpi CR l, mpi CR r) NE { return divmod(l, r).second; }
  CEXP mpi& operator+=(mpi CR r) NE { return (*this) = (*this) + r; }
  CEXP mpi& operator-=(mpi CR r) NE { return (*this) = (*this) - r; }
  CEXP mpi& operator*=(mpi CR r) NE { return (*this) = (*this) * r; }
  CEXP mpi& operator/=(mpi CR r) NE { return (*this) = (*this) / r; }
  CEXP mpi& operator%=(mpi CR r) NE { return (*this) = (*this) % r; }
  CEXP mpi operator-() CNE {
    if (is_zero()) return *this;
    auto ret = *this;
    ret.neg = !ret.neg;
    return ret;
  }
  CEXP mpi operator+() CNE { return *this; }
  friend CEXP auto operator<=>(mpi CR l, mpi CR r) NE { return cmp(l, r); }
  friend CEXP bool operator==(mpi CR l, mpi CR r) NE { return std::is_eq(l <=> r); }

  CEXP strn to_str() CNE {
    if (is_zero()) return "0";
    strn r;
    r.reserve(size() * 8 + 1);
    if (neg) r.push_back('-');
    char int_buf[11];
    auto res = std::to_chars(int_buf, int_buf + 11, back());
    r.append(int_buf, u32(res.ptr - int_buf));
    for (u32 i = (u32)size() - 2; ~i; --i) r.append(ict4::get((*this)[i] / 10000u), 4), r.append(ict4::get((*this)[i] % 10000u), 4);
    return r;
  }
  CEXP i64 to_i64() CNE {
    i64 res = uvec2i64(*this);
    if (neg) res = -res;
    return res;
  }
  CEXP i128 to_i128() CNE {
    i128 res = 0;
    for (u32 i = (u32)size() - 1; ~i; --i) res = res * D + (*this)[i];
    if (neg) res = -res;
    return res;
  }
  friend auto& operator>>(istream_c auto& is, mpi& m) NE {
    strn s;
    is >> s, m = mpi{s};
    return is;
  }
  friend auto& operator<<(ostream_c auto& os, mpi CR m) NE { return os << m.to_str(); }

 private:
  static CEXP vecu uadd(vec_like CR a, vec_like CR b) NE {
    vecu c(max(a.size(), b.size()) + 1);
    flt_ (u32, i, 0, (u32)a.size()) c[i] += a[i];
    flt_ (u32, i, 0, (u32)b.size()) c[i] += b[i];
    flt_ (u32, i, 0, (u32)c.size() - 1)
      if (c[i] >= D) c[i] -= D, ++c[i + 1];
    shrink_(c);
    return c;
  }
  static CEXP vecu usub(vec_like CR a, vec_like CR b) NE {
    assert(std::is_lteq(ucmp(b, a)));
    vecu c = a;
    u32 borrow = 0;
    flt_ (u32, i, 0, (u32)a.size()) {
      if (i < b.size()) borrow += b[i];
      if (c[i] -= borrow, borrow = 0; (i32)c[i] < 0) c[i] += D, borrow = 1;
    }
    assert(!borrow);
    shrink_(c);
    return c;
  }
  static CEXP vecu umul_3ntt(vec_like CR a, vec_like CR b) NE {
    if (a.empty() || b.empty()) return {};
    auto m = conv_u128(a, b);
    vecu c;
    c.reserve(m.size() + 3);
    u128 x = 0;
    for (u32 i = 0;; ++i) {
      if (i >= m.size() && !x) break;
      if (i < m.size()) x += m[i];
      c.push_back(u32(x % D)), x /= D;
    }
    shrink_(c);
    return c;
  }
  static CEXP vecu umul_bf(vec_like CR a, vec_like CR b) NE {
    if (a.empty() || b.empty()) return {};
    vecuu prod(a.size() + b.size() - 1 + 1);
    flt_ (u32, i, 0, (u32)a.size())
      flt_ (u32, j, 0, (u32)b.size())
        if ((prod[i + j] += (u64)a[i] * b[j]) >= 4_u64 * D * D) prod[i + j] -= 4_u64 * D * D, prod[i + j + 1] += 4_u64 * D;
    vecu c(prod.size() + 1);
    u64 x = 0;
    u32 i = 0;
    for (; i < prod.size(); ++i) x += prod[i], c[i] = u32(x % D), x /= D;
    while (x) c[i] = u32(x % D), x /= D, ++i;
    shrink_(c);
    return c;
  }
  static CEXP vecu umul(vec_like CR a, vec_like CR b) NE {
    if (is_0(a) || is_0(b)) return {};
    if (is_pm1(a)) return b;
    if (is_pm1(b)) return a;
    if (min(a.size(), b.size()) <= CONV_NAIVE_THRESHOLD) {
      retif_((a.size() < b.size()), umul_bf(b, a), umul_bf(a, b));
    } else return umul_3ntt(a, b);
  }
  // 0 <= A < 1e16, 1 <= B < 1e8
  static CEXP ptt<vecu> udivmod_li(vec_like CR a, vec_like CR b) NE {
    assert(a.size() <= 2 && b.size() == 1);
    i64 va = uvec2i64(a);
    u32 vb = b[0];
    return {int2vecu(va / vb), int2vecu(va % vb)};
  }
  // 0 <= A < 1e16, 1 <= B < 1e16
  static CEXP ptt<vecu> udivmod_ll(vec_like CR a, vec_like CR b) NE {
    assert(a.size() <= 2 && b.size() && b.size() <= 2);
    i64 va = uvec2i64(a), vb = uvec2i64(b);
    return {int2vecu(va / vb), int2vecu(va % vb)};
  }
  // 1 <= B < 1e8
  static CEXP ptt<vecu> udivmod_1e8(vec_like CR a, vec_like CR b) NE {
    if (assert(b.size() == 1); b[0] == 1) return {a, {}};
    if (a.size() <= 2) return udivmod_li(a, b);
    vecu quo(a.size());
    u64 d = 0;
    u32 b0 = b[0];
    for (u32 i = (u32)a.size() - 1; ~i; --i) d = d * D + a[i], assert(d < (u64)D * b0), quo[i] = u32(d / b0), d = d % b0;
    shrink_(quo);
    return {quo, d ? vecu{u32(d)} : vecu{}};
  }
  // 0 <= A, 1 <= B
  static CEXP ptt<vecu> udivmod_bf(vec_like CR a, vec_like CR b) NE {
    if (assert(!is_0(b) && b.size()); b.size() == 1) return udivmod_1e8(a, b);
    if (max(a.size(), b.size()) <= 2) return udivmod_ll(a, b);
    if (std::is_lt(ucmp(a, b))) return {{}, a};
    // B >= 1e8, A >= B
    u32 norm = D / (b.back() + 1);
    vecu x = umul(a, vecu{norm}), y = umul(b, vecu{norm});
    u32 yb = y.back();
    vecu quo(x.size() - y.size() + 1), rem(x.end() - (int)y.size(), x.end());
    for (u32 i = (u32)quo.size() - 1; ~i; --i) {
      if (rem.size() == y.size()) {
        if (std::is_lteq(ucmp(y, rem))) quo[i] = 1, rem = usub(rem, y);
      } else if (rem.size() > y.size()) {
        assert(y.size() + 1 == rem.size());
        u32 q = (u32)(((u64)rem[rem.size() - 1] * D + rem[rem.size() - 2]) / yb);
        vecu yq = umul(y, vecu{q});
        while (std::is_lt(ucmp(rem, yq))) --q, yq = usub(yq, y);
        rem = usub(rem, yq);
        while (std::is_lteq(ucmp(y, rem))) ++q, rem = usub(rem, y);
        quo[i] = q;
      }
      if (i) rem.insert(rem.begin(), x[i - 1]);
    }
    shrink_(quo), shrink_(rem);
    auto [q2, r2] = udivmod_1e8(rem, vecu{norm});
    assert(is_0(r2));
    return {quo, q2};
  }
  // 1 / a, abserr = B^{-deg}
  static CEXP vecu inv_(vec_like CR a, u32 deg) {
    assert(!a.empty() && D / 2 <= a.back() && a.back() < D);
    u32 k = deg, c = (u32)a.size();
    while (k > 64) k = (k + 1) / 2;
    vecu z(c + k + 1);
    z.back() = 1, z = udivmod_bf(z, a).first;
    while (k < deg) {
      vecu s = umul(z, z);
      s.insert(s.begin(), 0);
      u32 d = min(c, 2 * k + 1);
      vecu t{a.end() - d, a.end()}, u = umul(s, t);
      u.erase(u.begin(), u.begin() + d);
      vecu w(k + 1), w2 = uadd(z, z);
      copy(w2, std::back_inserter(w));
      (z = usub(w, u)).erase(z.begin()), k *= 2;
    }
    z.erase(z.begin(), z.begin() + k - deg);
    return z;
  }
  static CEXP ptt<vecu> udivmod(vec_like CR a, vec_like CR b) NE {
    if (assert(!is_0(b)); b.size() <= 64) return udivmod_bf(a, b);
    if ((int)(a.size() - b.size()) <= 64) return udivmod_bf(a, b);
    u32 norm = D / (b.back() + 1);
    vecu x = umul(a, vecu{norm}), y = umul(b, vecu{norm});
    u32 s = (u32)x.size(), t = (u32)y.size(), deg = s + 2 - t;
    vecu z = inv_(y, deg), q = umul(x, z);
    q.erase(q.begin(), q.begin() + t + deg);
    vecu yq = umul(y, vecu{q});
    while (std::is_lt(ucmp(x, yq))) q = usub(q, vecu{1}), yq = usub(yq, y);
    vecu r = usub(x, yq);
    while (std::is_lteq(ucmp(y, r))) q = uadd(q, vecu{1}), r = usub(r, y);
    shrink_(q), shrink_(r);
    auto [q2, r2] = udivmod_1e8(r, vecu{norm});
    assert(is_0(r2));
    return {q, q2};
  }

#undef vec_like
};

}  // namespace tifa_libs::math

#endif