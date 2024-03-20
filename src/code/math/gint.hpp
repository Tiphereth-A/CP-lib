#ifndef TIFALIBS_MATH_GINT
#define TIFALIBS_MATH_GINT

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class T, i64 M>
class gint {
  T r_, i_;

 public:
  constexpr gint(T const &real = T{}, T const &imag = T{}) : r_(real), i_(imag) {}

  constexpr T const &real() const { return r_; }
  constexpr T const &imag() const { return i_; }
  constexpr T norm() const { return r_ * r_ - i_ * i_ * M; }
  constexpr T &real() { return r_; }
  constexpr T &imag() { return i_; }
  constexpr void real(T const &x) { r_ = x; }
  constexpr void imag(T const &x) { i_ = x; }
  constexpr gint &operator+=(T const &x) {
    r_ += x;
    return *this;
  }
  constexpr gint &operator-=(T const &x) {
    r_ -= x;
    return *this;
  }
  constexpr gint &operator*=(T const &x) {
    r_ *= x;
    i_ *= x;
    return *this;
  }
  constexpr gint &operator/=(T const &x) {
    r_ /= x;
    i_ /= x;
    return *this;
  }
  constexpr gint &operator+=(gint const &x) {
    r_ += x.real();
    i_ += x.imag();
    return *this;
  }
  constexpr gint &operator-=(gint const &x) {
    r_ -= x.real();
    i_ -= x.imag();
    return *this;
  }
  constexpr gint &operator*=(gint const &x) {
    T _ = r_ * x.real() + i_ * x.imag() * M;
    i_ = r_ * x.imag() + i_ * x.real();
    r_ = _;
    return *this;
  }
  constexpr gint &operator/=(gint const &x) {
    const T _ = r_ * x.real() - i_ * x.imag() * M;
    const T n_ = x.norm();
    if constexpr (std::is_integral_v<T>) {
      auto div = [](T x, T y) {
        T a = x * 2 + y, b = y * 2;
        return a / b - (a % b < 0);
      };
      i_ = div(i_ * x.real() - r_ * x.imag(), n_);
      r_ = div(_, n_);
    } else {
      i_ = (i_ * x.real() - r_ * x.imag()) / n_;
      r_ = _ / n_;
    }
    return *this;
  }
  constexpr gint &operator%=(gint const &x) { return *this -= *this / x * x; }
  friend constexpr gint operator+(gint x, T const &y) { return x += y; }
  friend constexpr gint operator-(gint x, T const &y) { return x -= y; }
  friend constexpr gint operator*(gint x, T const &y) { return x *= y; }
  friend constexpr gint operator/(gint x, T const &y) { return x /= y; }
  friend constexpr gint operator+(gint x, gint const &y) { return x += y; }
  friend constexpr gint operator-(gint x, gint const &y) { return x -= y; }
  friend constexpr gint operator*(gint x, gint const &y) { return x *= y; }
  friend constexpr gint operator/(gint x, gint const &y) { return x /= y; }
  friend constexpr gint operator%(gint x, gint const &y) { return x %= y; }
  constexpr gint operator+() const { return *this; }
  constexpr gint operator-() const { return gint(-r_, -i_); }
  friend constexpr gint conj(gint const &x) { return gint{x.r_, -x.i_}; }
  friend constexpr T norm(gint const &x) { return x.norm(); }
  friend constexpr gint gcd(gint m, gint n) {
    while (n != gint{}) std::swap(m %= n, n);
    return m;
  }
  friend constexpr bool operator==(gint const &x, gint const &y) { return x.real() == y.real() && x.imag() == y.imag(); }
  friend std::istream &operator>>(std::istream &is, gint &x) { return is >> x.r_ >> x.i_; }
  friend std::ostream &operator<<(std::ostream &os, gint const &x) { return os << x.real() << ' ' << x.imag(); }
};

}  // namespace tifa_libs::math

#endif