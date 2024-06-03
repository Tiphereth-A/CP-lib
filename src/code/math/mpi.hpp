#ifndef TIFALIBS_MATH_MPI
#define TIFALIBS_MATH_MPI

#include "../conv/conv_u128.hpp"
#include "../fast/str2uint_si64.hpp"
#include "../util/traits.hpp"

namespace tifa_libs::math {

class mpi {
  bool neg;
  vecu dt;

 public:
  static CEXP u32 D = 100000000, lgD = 8;
  explicit CEXP mpi() : neg(false), dt() {}
  CEXP mpi(bool n, itlu x) : neg(n), dt(x) {}
  CEXP mpi(bool n, spnu d) : neg(n), dt(d.begin(), d.end()) {}
  template <int_c T>
  CEXP mpi(T x) : neg(false) {
    if CEXP (is_sint_v<T>)
      if (x < 0) neg = true, x = -x;
    while (x) dt.push_back(u32(to_uint_t<T>(x) % D)), x /= (T)D;
  }
  CEXP mpi(strn s) : neg(false) {
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
    if (u32 ofs = u32(s.size() - l) & 7; ofs) {
      flt_ (u32, i, l, l + ofs) _ = _ * 10 + (s[i] & 15);
      l += ofs;
    }
    if (l) s = s.substr(l);
    for (u32 ie = (u32)s.size(); ie >= lgD; ie -= lgD)
      dt.push_back(str2uint_si64(s.data() + ie - lgD));
    if (_) dt.push_back(_);
  }

  CEXP void set_neg(bool s) { neg = s; }
  CEXP bool is_neg() const { return neg; }
  CEXP vecu& data() { return dt; }
  CEXP vecu CR data() const { return dt; }
  friend CEXP mpi operator+(mpi CR l, mpi CR r) {
    if (l.neg == r.neg) return {l.neg, add_(l.dt, r.dt)};
    if (leq_(l.dt, r.dt)) {
      auto c = sub_(r.dt, l.dt);
      return {is0_(c) ? false : r.neg, c};
    }
    auto c = sub_(l.dt, r.dt);
    return {is0_(c) ? false : l.neg, c};
  }
  friend CEXP mpi operator-(mpi CR l, mpi CR r) { return l + (-r); }
  friend CEXP mpi operator*(mpi CR l, mpi CR r) {
    auto c = mul_(l.dt, r.dt);
    bool n = is0_(c) ? false : (l.neg ^ r.neg);
    return {n, c};
  }
  friend CEXP ptt<mpi> divmod(mpi CR l, mpi CR r) {
    auto dm = divmod_newton_(l.dt, r.dt);
    return {mpi{is0_(dm.first) ? false : l.neg != r.neg, dm.first}, mpi{is0_(dm.second) ? false : l.neg, dm.second}};
  }
  friend CEXP mpi operator/(mpi CR l, mpi CR r) { return divmod(l, r).first; }
  friend CEXP mpi operator%(mpi CR l, mpi CR r) { return divmod(l, r).second; }
  CEXP mpi& operator+=(mpi CR r) { return (*this) = (*this) + r; }
  CEXP mpi& operator-=(mpi CR r) { return (*this) = (*this) - r; }
  CEXP mpi& operator*=(mpi CR r) { return (*this) = (*this) * r; }
  CEXP mpi& operator/=(mpi CR r) { return (*this) = (*this) / r; }
  CEXP mpi& operator%=(mpi CR r) { return (*this) = (*this) % r; }
  CEXP mpi operator-() const {
    if (is_zero()) return *this;
    return {!neg, dt};
  }
  CEXP mpi operator+() const { return *this; }
  friend CEXP mpi abs(mpi CR m) { return {false, m.dt}; }
  CEXP bool is_zero() const { return is0_(dt); }
  friend CEXP bool operator==(mpi CR l, mpi CR r) { return l.neg == r.neg && l.dt == r.dt; }
  // clang-format off
  friend CEXP auto operator<=>(mpi  CR l, mpi  CR r) { return l == r ? 0 : neq_lt_(l, r) ? -1 : 1; }
  // clang-format on
  CEXP u32 size() const { return (u32)dt.size(); }
  CEXP void shrink() { shrink_(dt); }
  CEXP strn to_str() const {
    if (is_zero()) return "0";
    strn res;
    if (neg) res.push_back('-');
    for (u32 i = size() - 1; ~i; --i) res += itos_((u32)dt[i], i != size() - 1);
    return res;
  }
  CEXP i64 to_i64() const {
    i64 res = to_i64_(dt);
    return neg ? -res : res;
  }
  CEXP i128 to_i128() const {
    i128 res = 0;
    for (u32 i = (u32)dt.size() - 1; ~i; --i) res = res * D + dt[i];
    return neg ? -res : res;
  }
  friend std::istream& operator>>(std::istream& is, mpi& m) {
    strn s;
    return is >> s, m = mpi{s}, is;
  }
  friend std::ostream& operator<<(std::ostream& os, mpi CR m) { return os << m.to_str(); }

 private:
  static CEXP bool lt_(spnu a, spnu b) {
    if (a.size() != b.size()) return a.size() < b.size();
    for (u32 i = (u32)a.size() - 1; ~i; --i)
      if (a[i] != b[i]) return a[i] < b[i];
    return false;
  }
  static CEXP bool leq_(vecu CR a, vecu CR b) { return a == b || lt_(a, b); }
  // a < b (s.t. a != b)
  static CEXP bool neq_lt_(mpi CR l, mpi CR r) {
    assert(l != r);
    if (l.neg != r.neg) return l.neg;
    return lt_(l.dt, r.dt) ^ l.neg;
  }
  static CEXP bool is0_(spnu a) { return a.empty(); }
  static CEXP bool is1_(spnu a) { return a.size() == 1 && a[0] == 1; }
  static CEXP void shrink_(vecu& a) {
    while (a.size() && !a.back()) a.pop_back();
  }
  static CEXP vecu add_(vecu CR a, vecu CR b) {
    vecu c(max(a.size(), b.size()) + 1);
    flt_ (u32, i, 0, (u32)a.size()) c[i] += a[i];
    flt_ (u32, i, 0, (u32)b.size()) c[i] += b[i];
    flt_ (u32, i, 0, (u32)c.size() - 1)
      if (c[i] >= D) c[i] -= D, ++c[i + 1];
    return shrink_(c), c;
  }
  static CEXP vecu sub_(vecu CR a, vecu CR b) {
    assert(leq_(b, a));
    vecu c = a;
    u32 borrow = 0;
    flt_ (u32, i, 0, (u32)a.size()) {
      if (i < b.size()) borrow += b[i];
      if (c[i] -= borrow, borrow = 0; (i32)c[i] < 0) c[i] += D, borrow = 1;
    }
    assert(!borrow);
    return shrink_(c), c;
  }
  static CEXP vecu mul_3ntt_(vecu CR a, vecu CR b) {
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
    return shrink_(c), c;
  }
  static CEXP vecu mul_bf_(spnu a, spnu b) {
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
    return shrink_(c), c;
  }
  static CEXP vecu mul_(vecu CR a, vecu CR b) {
    if (is0_(a) || is0_(b)) return {};
    if (is1_(a)) return b;
    if (is1_(b)) return a;
    if (min(a.size(), b.size()) <= 128) return a.size() < b.size() ? mul_bf_(b, a) : mul_bf_(a, b);
    return mul_3ntt_(a, b);
  }
  // 0 <= A < 1e16, 1 <= B < 1e8
  static CEXP ptt<vecu> divmod_li_(spnu a, spnu b) {
    assert(a.size() <= 2 && b.size() == 1);
    i64 va = to_i64_(a);
    u32 vb = b[0];
    return {itov_(va / vb), itov_(va % vb)};
  }
  // 0 <= A < 1e16, 1 <= B < 1e16
  static CEXP ptt<vecu> divmod_ll_(spnu a, spnu b) {
    assert(a.size() <= 2 && b.size() && b.size() <= 2);
    i64 va = to_i64_(a), vb = to_i64_(b);
    return {itov_(va / vb), itov_(va % vb)};
  }
  // 1 <= B < 1e8
  static CEXP ptt<vecu> divmod_1e8_(vecu CR a, vecu CR b) {
    assert(b.size() == 1);
    if (b[0] == 1) return {a, {}};
    if (a.size() <= 2) return divmod_li_(a, b);
    vecu quo(a.size());
    u64 d = 0;
    u32 b0 = b[0];
    for (u32 i = (u32)a.size() - 1; ~i; --i) {
      d = d * D + a[i];
      assert(d < (u64)D * b0);
      quo[i] = u32(d / b0), d = d % b0;
    }
    shrink_(quo);
    return {quo, d ? vecu{u32(d)} : vecu{}};
  }
  // 0 <= A, 1 <= B
  static CEXP ptt<vecu> divmod_bf_(vecu CR a, vecu CR b) {
    assert(!is0_(b) && b.size());
    if (b.size() == 1) return divmod_1e8_(a, b);
    if (max(a.size(), b.size()) <= 2) return divmod_ll_(a, b);
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
  static CEXP vecu inv_(vecu CR a, u32 deg) {
    assert(!a.empty() && D / 2 <= a.back() && a.back() < D);
    u32 k = deg, c = (u32)a.size();
    while (k > 64) k = (k + 1) / 2;
    vecu z(c + k + 1);
    z.back() = 1, z = divmod_bf_(z, a).first;
    while (k < deg) {
      vecu s = mul_(z, z);
      s.insert(s.begin(), 0);
      u32 d = min(c, 2 * k + 1);
      vecu t{a.end() - d, a.end()}, u = mul_(s, t);
      u.erase(u.begin(), u.begin() + d);
      vecu w(k + 1), w2 = add_(z, z);
      std::ranges::copy(w2, std::back_inserter(w));
      (z = sub_(w, u)).erase(z.begin()), k *= 2;
    }
    return z.erase(z.begin(), z.begin() + k - deg), z;
  }
  static CEXP ptt<vecu> divmod_newton_(vecu CR a, vecu CR b) {
    assert(!is0_(b));
    if (b.size() <= 64) return divmod_bf_(a, b);
    if ((int)(a.size() - b.size()) <= 64) return divmod_bf_(a, b);
    u32 norm = D / (b.back() + 1);
    vecu x = mul_(a, {norm}), y = mul_(b, {norm});
    u32 s = (u32)x.size(), t = (u32)y.size(), deg = s + 2 - t;
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
  static CEXP strn itos_(u32 x, bool zero_padding) {
    assert(x < D);
    strn res;
    flt_ (u32, i, 0, lgD) res.push_back(char(48 + x % 10)), x /= 10;
    if (!zero_padding) {
      while (res.size() && res.back() == '0') res.pop_back();
      assert(!res.empty());
    }
    return std::ranges::reverse(res), res;
  }
  template <int_c T>
  static CEXP vecu itov_(T x) {
    if CEXP (is_sint_v<T>) assert(x >= 0);
    vecu res;
    while (x) res.push_back((u32)(x % D)), x /= D;
    return res;
  }
  static CEXP i64 to_i64_(spnu a) {
    i64 res = 0;
    for (u32 i = (u32)a.size() - 1; ~i; --i) res = res * D + a[i];
    return res;
  }
};

}  // namespace tifa_libs::math

#endif