#ifndef TIFALIBS_MATH_MINT_2E61N1
#define TIFALIBS_MATH_MINT_2E61N1

#include "../util/traits.hpp"
#include "../util/util.hpp"

namespace tifa_libs::math {

class mint_2e61n1 {
  u64 v_{};
  static constexpr u64 MOD = (1ull << 61) - 1;
  static constexpr u64 _30 = (1 << 30) - 1, _31 = (1u << 31) - 1;

  // clang-format off
  template <class T, std::enable_if_t<is_uint<T>::value> * = nullptr>
  static constexpr u64 mod_(T x) { return x < MOD ? (u64)x : (x = (x & MOD) + ((u64)x >> 61)) > MOD ? x - MOD : (u64)x; }
  template <class T, std::enable_if_t<is_sint<T>::value> * = nullptr>
  static constexpr u64 mod_(T x) { return x >= 0 ? mod_(to_uint_t<T>(x)) : MOD - mod_(to_uint_t<T>(-x)); }
  // clang-format on

 public:
  static constexpr u64 mod() { return MOD; }

  constexpr mint_2e61n1() {}
  template <class T, std::enable_if_t<std::is_integral_v<T>> * = nullptr>
  constexpr mint_2e61n1(T v) : v_(mod_(v)) {}

  constexpr u64 val() const { return v_; }
  constexpr u64 &data() { return v_; }
  constexpr u64 const &data() const { return v_; }
  template <class T, std::enable_if_t<std::is_integral_v<T>> * = nullptr>
  explicit operator T() const { return (T)(val()); }
  constexpr mint_2e61n1 operator-() const { return MOD - v_; }
  constexpr mint_2e61n1 inv() const {
    i64 x1 = 1, x3 = 0, a = (i64)val(), b = MOD;
    while (b != 0) {
      i64 q = a / b, x1_old = x1, a_old = a;
      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;
    }
    return mint_2e61n1(x1);
  }
  constexpr mint_2e61n1 &operator+=(mint_2e61n1 const &r) {
    v_ = mod_(v_ + r.v_);
    return *this;
  }
  constexpr mint_2e61n1 &operator-=(mint_2e61n1 const &r) {
    v_ < r.v_ ? v_ = mod_(v_ + MOD - r.v_) : v_ -= r.v_;
    return *this;
  }
  constexpr mint_2e61n1 &operator*=(mint_2e61n1 const &r) {
    u64 au = v_ >> 31, ad = v_ & _31, bu = r.v_ >> 31, bd = r.v_ & _31, _ = ad * bu + au * bd;
    v_ = mod_(((au * bu) << 1) + ad * bd + ((_ & _30) << 31) + (_ >> 30));
    return *this;
  }
  constexpr mint_2e61n1 &operator/=(mint_2e61n1 const &r) { return operator*=(r.inv()); }
  friend constexpr mint_2e61n1 operator+(mint_2e61n1 const &l, mint_2e61n1 const &r) { return mint_2e61n1(l) += r; }
  friend constexpr mint_2e61n1 operator-(mint_2e61n1 const &l, mint_2e61n1 const &r) { return mint_2e61n1(l) -= r; }
  friend constexpr mint_2e61n1 operator*(mint_2e61n1 const &l, mint_2e61n1 const &r) { return mint_2e61n1(l) *= r; }
  friend constexpr mint_2e61n1 operator/(mint_2e61n1 const &l, mint_2e61n1 const &r) { return mint_2e61n1(l) /= r; }
  friend constexpr bool operator==(mint_2e61n1 const &l, mint_2e61n1 const &r) { return l.v_ == r.v_; }
  friend constexpr bool operator!=(mint_2e61n1 const &l, mint_2e61n1 const &r) { return l.v_ != r.v_; }
  friend constexpr bool operator<(mint_2e61n1 const &l, mint_2e61n1 const &r) { return l.val() < r.val(); }
  friend std::istream &operator>>(std::istream &is, mint_2e61n1 &r) {
    i64 x;
    is >> x;
    r = mint_2e61n1(x);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, mint_2e61n1 const &r) { return os << r.val(); }
  friend constexpr u64 abs(mint_2e61n1 const &x) { return x.val(); }
};

}  // namespace tifa_libs::math

#endif