#ifndef TIFA_LIBS_MATH_MPI
#define TIFA_LIBS_MATH_MPI

#include "../conv/conv_u128.hpp"
#include "../util/str2uint_1e8.hpp"
#include "../util/traits.hpp"

namespace tifa_libs::math {

class mpi {
  static constexpr u32 D = 100000000, logD = 8;
  bool neg;
  vec<u32> dt;

 public:
  explicit mpi() : neg(false), dt() {}
  mpi(bool n, vec<u32> const& d) : neg(n), dt(d) {}
  template <class T, std::enable_if_t<is_int<T>::value>* = nullptr>
  mpi(T x) : neg(false) {
    if constexpr (is_sint<T>::value)
      if (x < 0) neg = true, x = -x;
    while (x) dt.push_back(x % D), x /= D;
  }
  mpi(std::string_view s) : neg(false) {
    assert(!s.empty());
    if (s.size() == 1u && s[0] == '0') return;
    size_t l = 0;
    if (s[0] == '-') ++l, neg = true;
    for (size_t ie = s.size(); l + logD <= ie; l += logD) dt.push_back(str2uint_1e8(s.data() + l));
    if (l == s.size()) return;
    dt.push_back(0);
    for (; l < s.size(); ++l) dt.back() = dt.back() * 10 + (s[l] & 15);
  }

  constexpr static u32 digit() { return D; }
  constexpr static u32 log_digit() { return logD; }
  void set_neg(bool s) { neg = s; }
  bool is_neg() const { return neg; }
  vec<u32>& data() { return dt; }
  vec<u32> data() const { return dt; }

  friend mpi operator+(mpi const& lhs, mpi const& rhs) {
    if (lhs.neg == rhs.neg) return {lhs.neg, add_(lhs.dt, rhs.dt)};
    if (leq_(lhs.dt, rhs.dt)) {
      auto c = sub_(rhs.dt, lhs.dt);
      return {is0_(c) ? false : rhs.neg, c};
    }
    auto c = sub_(lhs.dt, rhs.dt);
    return {is0_(c) ? false : lhs.neg, c};
  }
  friend mpi operator-(mpi const& lhs, mpi const& rhs) { return lhs + (-rhs); }
  friend mpi operator*(mpi const& lhs, mpi const& rhs) {
    auto c = mul_(lhs.dt, rhs.dt);
    bool n = is0_(c) ? false : (lhs.neg ^ rhs.neg);
    return {n, c};
  }
  friend ptt<mpi> divmod(mpi const& lhs, mpi const& rhs) {
    auto dm = divmod_newton_(lhs.dt, rhs.dt);
    return {mpi{is0_(dm.first) ? false : lhs.neg != rhs.neg, dm.first}, mpi{is0_(dm.second) ? false : lhs.neg, dm.second}};
  }
  friend mpi operator/(mpi const& lhs, mpi const& rhs) { return divmod(lhs, rhs).first; }
  friend mpi operator%(mpi const& lhs, mpi const& rhs) { return divmod(lhs, rhs).second; }

  mpi& operator+=(mpi const& rhs) { return (*this) = (*this) + rhs; }
  mpi& operator-=(mpi const& rhs) { return (*this) = (*this) - rhs; }
  mpi& operator*=(mpi const& rhs) { return (*this) = (*this) * rhs; }
  mpi& operator/=(mpi const& rhs) { return (*this) = (*this) / rhs; }
  mpi& operator%=(mpi const& rhs) { return (*this) = (*this) % rhs; }

  mpi operator-() const {
    if (is_zero()) return *this;
    return {!neg, dt};
  }
  mpi operator+() const { return *this; }
  friend mpi abs(mpi const& m) { return {false, m.dt}; }
  bool is_zero() const { return is0_(dt); }

  friend bool operator==(mpi const& lhs, mpi const& rhs) { return lhs.neg == rhs.neg && lhs.dt == rhs.dt; }
  friend bool operator!=(mpi const& lhs, mpi const& rhs) { return !(lhs == rhs); }
  friend bool operator<(mpi const& lhs, mpi const& rhs) { return lhs == rhs ? false : neq_lt_(lhs, rhs); }
  friend bool operator<=(mpi const& lhs, mpi const& rhs) { return lhs == rhs ? true : neq_lt_(lhs, rhs); }
  friend bool operator>(mpi const& lhs, mpi const& rhs) { return lhs == rhs ? false : neq_lt_(rhs, lhs); }
  friend bool operator>=(mpi const& lhs, mpi const& rhs) { return lhs == rhs ? true : neq_lt_(rhs, lhs); }

  size_t size() const { return dt.size(); }
  void shrink() { shrink_(dt); }

  std::string to_str() const {
    if (is_zero()) return "0";
    std::string res;
    if (neg) res.push_back('-');
    for (size_t i = size() - 1; ~i; --i) res += itos_((u32)dt[i], i != size() - 1);
    return res;
  }
  i64 to_i64() const {
    i64 res = to_i64_(dt);
    return neg ? -res : res;
  }
  i128 to_i128() const {
    i128 res = 0;
    for (size_t i = dt.size() - 1; ~i; --i) res = res * D + dt[i];
    return neg ? -res : res;
  }

  friend std::istream& operator>>(std::istream& is, mpi& m) {
    std::string s;
    is >> s;
    m = mpi{s};
    return is;
  }
  friend std::ostream& operator<<(std::ostream& os, mpi const& m) { return os << m.to_str(); }

 private:
  static bool lt_(vec<u32> const& a, vec<u32> const& b) {
    if (a.size() != b.size()) return a.size() < b.size();
    for (size_t i = a.size() - 1; ~i; --i)
      if (a[i] != b[i]) return a[i] < b[i];
    return false;
  }
  static bool leq_(vec<u32> const& a, vec<u32> const& b) { return a == b || lt_(a, b); }
  // a < b (s.t. a != b)
  static bool neq_lt_(mpi const& lhs, mpi const& rhs) {
    assert(lhs != rhs);
    if (lhs.neg != rhs.neg) return lhs.neg;
    return lt_(lhs.dt, rhs.dt) ^ lhs.neg;
  }
  static bool is0_(vec<u32> const& a) { return a.empty(); }
  static bool is1_(vec<u32> const& a) { return a.size() == 1 && a[0] == 1; }
  static void shrink_(vec<u32>& a) {
    while (a.size() && !a.back()) a.pop_back();
  }

  static vec<u32> add_(vec<u32> const& a, vec<u32> const& b) {
    vec<u32> c(std::max(a.size(), b.size()) + 1);
    for (size_t i = 0; i < a.size(); ++i) c[i] += a[i];
    for (size_t i = 0; i < b.size(); ++i) c[i] += b[i];
    for (size_t i = 0; i < c.size() - 1; ++i)
      if (c[i] >= D) c[i] -= D, c[i + 1]++;
    shrink_(c);
    return c;
  }
  static vec<u32> sub_(vec<u32> const& a, vec<u32> const& b) {
    assert(leq_(b, a));
    vec<u32> c = a;
    u32 borrow = 0;
    for (size_t i = 0; i < a.size(); ++i) {
      if (i < b.size()) borrow += b[i];
      c[i] -= borrow;
      borrow = 0;
      if ((i32)c[i] < 0) c[i] += D, borrow = 1;
    }
    assert(!borrow);
    shrink_(c);
    return c;
  }
  static vec<u32> mul_3ntt_(vec<u32> const& a, vec<u32> const& b) {
    if (a.empty() || b.empty()) return {};
    auto m = conv_u128(a, b);
    vec<u32> c;
    c.reserve(m.size() + 3);
    u128 x = 0;
    for (size_t i = 0;; ++i) {
      if (i >= m.size() && !x) break;
      if (i < m.size()) x += m[i];
      c.push_back(u32(x % D));
      x /= D;
    }
    shrink_(c);
    return c;
  }
  static vec<u32> mul_bf_(vec<u32> const& a, vec<u32> const& b) {
    if (a.empty() || b.empty()) return {};
    vec<u64> prod(a.size() + b.size() - 1 + 1);
    for (size_t i = 0; i < a.size(); ++i)
      for (size_t j = 0; j < b.size(); ++j)
        if ((prod[i + j] += (u64)a[i] * b[j]) >= (u64)4 * D * D) prod[i + j] -= (u64)4 * D * D, prod[i + j + 1] += (u64)4 * D;
    vec<u32> c(prod.size() + 1);
    u64 x = 0;
    size_t i = 0;
    for (; i < prod.size(); ++i) x += prod[i], c[i] = u32(x % D), x /= D;
    while (x) c[i] = u32(x % D), x /= D, ++i;
    shrink_(c);
    return c;
  }
  static vec<u32> mul_(vec<u32> const& a, vec<u32> const& b) {
    if (is0_(a) || is0_(b)) return {};
    if (is1_(a)) return b;
    if (is1_(b)) return a;
    if (std::min(a.size(), b.size()) <= 128) return a.size() < b.size() ? mul_bf_(b, a) : mul_bf_(a, b);
    return mul_3ntt_(a, b);
  }
  // 0 <= A < 1e16, 1 <= B < 1e8
  static ptt<vec<u32>> divmod_li_(vec<u32> const& a, vec<u32> const& b) {
    assert(a.size() <= 2 && b.size() == 1);
    i64 va = to_i64_(a);
    u32 vb = b[0];
    return {itov_(va / vb), itov_(va % vb)};
  }
  // 0 <= A < 1e16, 1 <= B < 1e16
  static ptt<vec<u32>> divmod_ll_(vec<u32> const& a, vec<u32> const& b) {
    assert(a.size() <= 2 && b.size() && b.size() <= 2);
    i64 va = to_i64_(a), vb = to_i64_(b);
    return {itov_(va / vb), itov_(va % vb)};
  }
  // 1 <= B < 1e8
  static ptt<vec<u32>> divmod_1e8_(vec<u32> const& a, vec<u32> const& b) {
    assert(b.size() == 1);
    if (b[0] == 1) return {a, {}};
    if (a.size() <= 2) return divmod_li_(a, b);
    vec<u32> quo(a.size());
    u64 d = 0;
    u32 b0 = b[0];
    for (size_t i = a.size() - 1; ~i; --i) {
      d = d * D + a[i];
      assert(d < (u64)D * b0);
      quo[i] = u32(d / b0);
      d = d % b0;
    }
    shrink_(quo);
    return {quo, d ? vec<u32>{u32(d)} : vec<u32>{}};
  }
  // 0 <= A, 1 <= B
  static ptt<vec<u32>> divmod_bf_(vec<u32> const& a, vec<u32> const& b) {
    assert(!is0_(b) && b.size());
    if (b.size() == 1) return divmod_1e8_(a, b);
    if (std::max(a.size(), b.size()) <= 2) return divmod_ll_(a, b);
    if (lt_(a, b)) return {{}, a};
    // B >= 1e8, A >= B
    u32 norm = D / (b.back() + 1);
    vec<u32> x = mul_(a, {norm}), y = mul_(b, {norm});
    u32 yb = y.back();
    vec<u32> quo(x.size() - y.size() + 1), rem(x.end() - (int)y.size(), x.end());
    for (size_t i = quo.size() - 1; ~i; --i) {
      if (rem.size() == y.size()) {
        if (leq_(y, rem)) quo[i] = 1, rem = sub_(rem, y);
      } else if (rem.size() > y.size()) {
        assert(y.size() + 1 == rem.size());
        u32 q = (u32)(((u64)rem[rem.size() - 1] * D + rem[rem.size() - 2]) / yb);
        vec<u32> yq = mul_(y, {q});
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
  static vec<u32> inv_(vec<u32> const& a, u32 deg) {
    assert(!a.empty() && D / 2 <= a.back() and a.back() < D);
    u32 k = deg, c = (u32)a.size();
    while (k > 64) k = (k + 1) / 2;
    vec<u32> z(size_t(c + k + 1));
    z.back() = 1;
    z = divmod_bf_(z, a).first;
    while (k < deg) {
      vec<u32> s = mul_(z, z);
      s.insert(s.begin(), 0);
      u32 d = std::min(c, 2 * k + 1);
      vec<u32> t{a.end() - d, a.end()}, u = mul_(s, t);
      u.erase(u.begin(), u.begin() + d);
      vec<u32> w(size_t(k + 1)), w2 = add_(z, z);
      std::copy(w2.begin(), w2.end(), std::back_inserter(w));
      (z = sub_(w, u)).erase(z.begin());
      k *= 2;
    }
    z.erase(z.begin(), z.begin() + k - deg);
    return z;
  }

  static ptt<vec<u32>> divmod_newton_(vec<u32> const& a, vec<u32> const& b) {
    assert(!is0_(b));
    if (b.size() <= 64) return divmod_bf_(a, b);
    if ((int)(a.size() - b.size()) <= 64) return divmod_bf_(a, b);
    u32 norm = D / (b.back() + 1);
    vec<u32> x = mul_(a, {norm}), y = mul_(b, {norm});
    u32 s = (u32)x.size(), t = (u32)y.size();
    u32 deg = s + 2 - t;
    vec<u32> z = inv_(y, deg), q = mul_(x, z);
    q.erase(q.begin(), q.begin() + t + deg);
    vec<u32> yq = mul_(y, {q});
    while (lt_(x, yq)) q = sub_(q, {1}), yq = sub_(yq, y);
    vec<u32> r = sub_(x, yq);
    while (leq_(y, r)) q = add_(q, {1}), r = sub_(r, y);
    shrink_(q), shrink_(r);
    auto [q2, r2] = divmod_1e8_(r, {norm});
    assert(is0_(r2));
    return {q, q2};
  }

  static std::string itos_(u32 x, bool zero_padding) {
    assert(x < D);
    std::string res;
    for (u32 i = 0; i < logD; ++i) res.push_back(char(48 + x % 10)), x /= 10;
    if (!zero_padding) {
      while (res.size() && res.back() == '0') res.pop_back();
      assert(!res.empty());
    }
    std::reverse(res.begin(), res.end());
    return res;
  }
  template <class T, std::enable_if_t<is_int<T>::value>* = nullptr>
  static vec<u32> itov_(T x) {
    if constexpr (is_sint<T>::value) assert(x >= 0);
    vec<u32> res;
    while (x) res.push_back((u32)(x % D)), x /= D;
    return res;
  }
  static i64 to_i64_(vec<u32> const& a) {
    i64 res = 0;
    for (size_t i = a.size() - 1; ~i; --i) res = res * D + a[i];
    return res;
  }
};

}  // namespace tifa_libs::math

#endif