#ifndef TIFALIBS_MATH_MPI
#define TIFALIBS_MATH_MPI

#include "../conv/conv_u128.hpp"
#include "../fast/str2uint_si64.hpp"
#include "../util/traits.hpp"

namespace tifa_libs::math {

class mpi {
  static constexpr u32 D = 100000000, lgD = 8;
  bool neg;
  vecu dt;

 public:
  explicit constexpr mpi() : neg(false), dt() {}
  constexpr mpi(bool n, vecu const& d) : neg(n), dt(d) {}
  template <int_c T>
  constexpr mpi(T x) : neg(false) {
    if constexpr (is_sint_v<T>)
      if (x < 0) neg = true, x = -x;
    while (x) dt.push_back(u32(to_uint_t<T>(x) % D)), x /= (T)D;
  }
  constexpr mpi(strn s) : neg(false) {
    assert(!s.empty());
    if (s.size() == 1u) {
      if (s[0] == '0') return;
      assert(isdigit(s[0]));
      dt.push_back(s[0] & 15);
      return;
    }
    u32 l = 0;
    if (s[0] == '-') ++l, neg = true;
    u32 _ = 0;
    if ((s.size() - l) & 7) {
      for (u32 i = l; i < l + ((s.size() - l) & 7); ++i) _ = _ * 10 + (s[i] & 15);
      l += (s.size() - l) & 7;
    }
    if (l) s = s.substr(l);
    for (u32 ie = (u32)s.size(); ie >= lgD; ie -= lgD)
      dt.push_back(str2uint_si64(s.data() + ie - lgD));
    if (_) dt.push_back(_);
  }

  static constexpr u32 digit() { return D; }
  static constexpr u32 log_digit() { return lgD; }
  constexpr void set_neg(bool s) { neg = s; }
  constexpr bool is_neg() const { return neg; }
  constexpr vecu& data() { return dt; }
  constexpr vecu const& data() const { return dt; }

  friend constexpr mpi operator+(mpi const& l, mpi const& r) {
    if (l.neg == r.neg) return {l.neg, add_(l.dt, r.dt)};
    if (leq_(l.dt, r.dt)) {
      auto c = sub_(r.dt, l.dt);
      return {is0_(c) ? false : r.neg, c};
    }
    auto c = sub_(l.dt, r.dt);
    return {is0_(c) ? false : l.neg, c};
  }
  friend constexpr mpi operator-(mpi const& l, mpi const& r) { return l + (-r); }
  friend constexpr mpi operator*(mpi const& l, mpi const& r) {
    auto c = mul_(l.dt, r.dt);
    bool n = is0_(c) ? false : (l.neg ^ r.neg);
    return {n, c};
  }
  friend constexpr ptt<mpi> divmod(mpi const& l, mpi const& r) {
    auto dm = divmod_newton_(l.dt, r.dt);
    return {mpi{is0_(dm.first) ? false : l.neg != r.neg, dm.first}, mpi{is0_(dm.second) ? false : l.neg, dm.second}};
  }
  friend constexpr mpi operator/(mpi const& l, mpi const& r) { return divmod(l, r).first; }
  friend constexpr mpi operator%(mpi const& l, mpi const& r) { return divmod(l, r).second; }

  constexpr mpi& operator+=(mpi const& r) { return (*this) = (*this) + r; }
  constexpr mpi& operator-=(mpi const& r) { return (*this) = (*this) - r; }
  constexpr mpi& operator*=(mpi const& r) { return (*this) = (*this) * r; }
  constexpr mpi& operator/=(mpi const& r) { return (*this) = (*this) / r; }
  constexpr mpi& operator%=(mpi const& r) { return (*this) = (*this) % r; }

  constexpr mpi operator-() const {
    if (is_zero()) return *this;
    return {!neg, dt};
  }
  constexpr mpi operator+() const { return *this; }
  friend constexpr mpi abs(mpi const& m) { return {false, m.dt}; }
  constexpr bool is_zero() const { return is0_(dt); }

  friend constexpr bool operator==(mpi const& l, mpi const& r) { return l.neg == r.neg && l.dt == r.dt; }
  // clang-format off
  friend constexpr auto operator<=>(mpi const& l, mpi const& r) { return l == r ? 0 : neq_lt_(l, r) ? -1 : 1; }
  // clang-format on

  constexpr u32 size() const { return (u32)dt.size(); }
  constexpr void shrink() { shrink_(dt); }

  constexpr strn to_str() const {
    if (is_zero()) return "0";
    strn res;
    if (neg) res.push_back('-');
    for (u32 i = size() - 1; ~i; --i) res += itos_((u32)dt[i], i != size() - 1);
    return res;
  }
  constexpr i64 to_i64() const {
    i64 res = to_i64_(dt);
    return neg ? -res : res;
  }
  constexpr i128 to_i128() const {
    i128 res = 0;
    for (u32 i = (u32)dt.size() - 1; ~i; --i) res = res * D + dt[i];
    return neg ? -res : res;
  }

  friend std::istream& operator>>(std::istream& is, mpi& m) {
    strn s;
    is >> s;
    m = mpi{s};
    return is;
  }
  friend std::ostream& operator<<(std::ostream& os, mpi const& m) { return os << m.to_str(); }

 private:
  static constexpr bool lt_(vecu const& a, vecu const& b) {
    if (a.size() != b.size()) return a.size() < b.size();
    for (u32 i = (u32)a.size() - 1; ~i; --i)
      if (a[i] != b[i]) return a[i] < b[i];
    return false;
  }
  static constexpr bool leq_(vecu const& a, vecu const& b) { return a == b || lt_(a, b); }
  // a < b (s.t. a != b)
  static constexpr bool neq_lt_(mpi const& l, mpi const& r) {
    assert(l != r);
    if (l.neg != r.neg) return l.neg;
    return lt_(l.dt, r.dt) ^ l.neg;
  }
  static constexpr bool is0_(vecu const& a) { return a.empty(); }
  static constexpr bool is1_(vecu const& a) { return a.size() == 1 && a[0] == 1; }
  static constexpr void shrink_(vecu& a) {
    while (a.size() && !a.back()) a.pop_back();
  }

  static constexpr vecu add_(vecu const& a, vecu const& b) {
    vecu c(std::max(a.size(), b.size()) + 1);
    for (u32 i = 0; i < a.size(); ++i) c[i] += a[i];
    for (u32 i = 0; i < b.size(); ++i) c[i] += b[i];
    for (u32 i = 0; i < c.size() - 1; ++i)
      if (c[i] >= D) c[i] -= D, c[i + 1]++;
    shrink_(c);
    return c;
  }
  static constexpr vecu sub_(vecu const& a, vecu const& b) {
    assert(leq_(b, a));
    vecu c = a;
    u32 borrow = 0;
    for (u32 i = 0; i < a.size(); ++i) {
      if (i < b.size()) borrow += b[i];
      c[i] -= borrow;
      borrow = 0;
      if ((i32)c[i] < 0) c[i] += D, borrow = 1;
    }
    assert(!borrow);
    shrink_(c);
    return c;
  }
  static constexpr vecu mul_3ntt_(vecu const& a, vecu const& b) {
    if (a.empty() || b.empty()) return {};
    auto m = conv_u128(a, b);
    vecu c;
    c.reserve(m.size() + 3);
    u128 x = 0;
    for (u32 i = 0;; ++i) {
      if (i >= m.size() && !x) break;
      if (i < m.size()) x += m[i];
      c.push_back(u32(x % D));
      x /= D;
    }
    shrink_(c);
    return c;
  }
  static constexpr vecu mul_bf_(vecu const& a, vecu const& b) {
    if (a.empty() || b.empty()) return {};
    vecu64 prod(a.size() + b.size() - 1 + 1);
    for (u32 i = 0; i < a.size(); ++i)
      for (u32 j = 0; j < b.size(); ++j)
        if ((prod[i + j] += (u64)a[i] * b[j]) >= 4_u64 * D * D) prod[i + j] -= 4_u64 * D * D, prod[i + j + 1] += 4_u64 * D;
    vecu c(prod.size() + 1);
    u64 x = 0;
    u32 i = 0;
    for (; i < prod.size(); ++i) x += prod[i], c[i] = u32(x % D), x /= D;
    while (x) c[i] = u32(x % D), x /= D, ++i;
    shrink_(c);
    return c;
  }
  static constexpr vecu mul_(vecu const& a, vecu const& b) {
    if (is0_(a) || is0_(b)) return {};
    if (is1_(a)) return b;
    if (is1_(b)) return a;
    if (std::min(a.size(), b.size()) <= 128) return a.size() < b.size() ? mul_bf_(b, a) : mul_bf_(a, b);
    return mul_3ntt_(a, b);
  }
  // 0 <= A < 1e16, 1 <= B < 1e8
  static constexpr ptt<vecu> divmod_li_(vecu const& a, vecu const& b) {
    assert(a.size() <= 2 && b.size() == 1);
    i64 va = to_i64_(a);
    u32 vb = b[0];
    return {itov_(va / vb), itov_(va % vb)};
  }
  // 0 <= A < 1e16, 1 <= B < 1e16
  static constexpr ptt<vecu> divmod_ll_(vecu const& a, vecu const& b) {
    assert(a.size() <= 2 && b.size() && b.size() <= 2);
    i64 va = to_i64_(a), vb = to_i64_(b);
    return {itov_(va / vb), itov_(va % vb)};
  }
  // 1 <= B < 1e8
  static constexpr ptt<vecu> divmod_1e8_(vecu const& a, vecu const& b) {
    assert(b.size() == 1);
    if (b[0] == 1) return {a, {}};
    if (a.size() <= 2) return divmod_li_(a, b);
    vecu quo(a.size());
    u64 d = 0;
    u32 b0 = b[0];
    for (u32 i = (u32)a.size() - 1; ~i; --i) {
      d = d * D + a[i];
      assert(d < (u64)D * b0);
      quo[i] = u32(d / b0);
      d = d % b0;
    }
    shrink_(quo);
    return {quo, d ? vecu{u32(d)} : vecu{}};
  }
  // 0 <= A, 1 <= B
  static constexpr ptt<vecu> divmod_bf_(vecu const& a, vecu const& b) {
    assert(!is0_(b) && b.size());
    if (b.size() == 1) return divmod_1e8_(a, b);
    if (std::max(a.size(), b.size()) <= 2) return divmod_ll_(a, b);
    if (lt_(a, b)) return {{}, a};
    // B >= 1e8, A >= B
    u32 norm = D / (b.back() + 1);
    vecu x = mul_(a, {norm}), y = mul_(b, {norm});
    u32 yb = y.back();
    vecu quo(x.size() - y.size() + 1), rem(x.end() - (int)y.size(), x.end());
    for (u32 i = (u32)quo.size() - 1; ~i; --i) {
      if (rem.size() == y.size()) {
        if (leq_(y, rem)) quo[i] = 1, rem = sub_(rem, y);
      } else if (rem.size() > y.size()) {
        assert(y.size() + 1 == rem.size());
        u32 q = (u32)(((u64)rem[rem.size() - 1] * D + rem[rem.size() - 2]) / yb);
        vecu yq = mul_(y, {q});
        while (lt_(rem, yq)) --q, yq = sub_(yq, y);
        rem = sub_(rem, yq);
        while (leq_(y, rem)) ++q, rem = sub_(rem, y);
        quo[i] = q;
      }
      if (i) rem.insert(rem.begin(), x[i - 1]);
    }
    shrink_(quo), shrink_(rem);
    auto [q2, r2] = divmod_1e8_(rem, {norm});
    assert(is0_(r2));
    return {quo, q2};
  }

  // 1 / a, abserr = B^{-deg}
  static constexpr vecu inv_(vecu const& a, u32 deg) {
    assert(!a.empty() && D / 2 <= a.back() && a.back() < D);
    u32 k = deg, c = (u32)a.size();
    while (k > 64) k = (k + 1) / 2;
    vecu z(c + k + 1);
    z.back() = 1;
    z = divmod_bf_(z, a).first;
    while (k < deg) {
      vecu s = mul_(z, z);
      s.insert(s.begin(), 0);
      u32 d = std::min(c, 2 * k + 1);
      vecu t{a.end() - d, a.end()}, u = mul_(s, t);
      u.erase(u.begin(), u.begin() + d);
      vecu w(k + 1), w2 = add_(z, z);
      std::ranges::copy(w2, std::back_inserter(w));
      (z = sub_(w, u)).erase(z.begin());
      k *= 2;
    }
    z.erase(z.begin(), z.begin() + k - deg);
    return z;
  }

  static constexpr ptt<vecu> divmod_newton_(vecu const& a, vecu const& b) {
    assert(!is0_(b));
    if (b.size() <= 64) return divmod_bf_(a, b);
    if ((int)(a.size() - b.size()) <= 64) return divmod_bf_(a, b);
    u32 norm = D / (b.back() + 1);
    vecu x = mul_(a, {norm}), y = mul_(b, {norm});
    u32 s = (u32)x.size(), t = (u32)y.size();
    u32 deg = s + 2 - t;
    vecu z = inv_(y, deg), q = mul_(x, z);
    q.erase(q.begin(), q.begin() + t + deg);
    vecu yq = mul_(y, {q});
    while (lt_(x, yq)) q = sub_(q, {1}), yq = sub_(yq, y);
    vecu r = sub_(x, yq);
    while (leq_(y, r)) q = add_(q, {1}), r = sub_(r, y);
    shrink_(q), shrink_(r);
    auto [q2, r2] = divmod_1e8_(r, {norm});
    assert(is0_(r2));
    return {q, q2};
  }

  static constexpr strn itos_(u32 x, bool zero_padding) {
    assert(x < D);
    strn res;
    for (u32 i = 0; i < lgD; ++i) res.push_back(char(48 + x % 10)), x /= 10;
    if (!zero_padding) {
      while (res.size() && res.back() == '0') res.pop_back();
      assert(!res.empty());
    }
    std::ranges::reverse(res);
    return res;
  }
  template <int_c T>
  static constexpr vecu itov_(T x) {
    if constexpr (is_sint_v<T>) assert(x >= 0);
    vecu res;
    while (x) res.push_back((u32)(x % D)), x /= D;
    return res;
  }
  static constexpr i64 to_i64_(vecu const& a) {
    i64 res = 0;
    for (u32 i = (u32)a.size() - 1; ~i; --i) res = res * D + a[i];
    return res;
  }
};

}  // namespace tifa_libs::math

#endif