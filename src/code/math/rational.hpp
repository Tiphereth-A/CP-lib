#ifndef TIFALIBS_MATH_RATIONAL
#define TIFALIBS_MATH_RATIONAL

#include "../nt/gcd.hpp"

namespace tifa_libs::math {

template <int_c T>
struct rational {
  T num, den;

  CEXP rational(T numerator = T(0), T denominator = T(1)) : num(numerator), den(denominator) {
    assert(den != 0);
    if (num == 0) den = 1;
    else {
      const T g = (T)gcd(num, den);
      num /= g, den /= g;
      if CEXP (std::is_signed_v<T>)
        if (den < 0) num = -num, den = -den;
    }
  }

  CEXP rational &operator+=(T x) {
    num += x * den;
    return *this;
  }
  CEXP rational &operator-=(T x) {
    num -= x * den;
    return *this;
  }
  CEXP rational &operator*=(T x) {
    const T g = (T)gcd(x, den);
    num *= x / g, den /= g;
    return *this;
  }
  CEXP rational &operator/=(T x) {
    assert(x);
    const T g = (T)gcd(x, num);
    num /= g, den *= x / g;
    if CEXP (std::is_signed_v<T>)
      if (den < 0) num = -num, den = -den;
    return *this;
  }
  CEXP rational &operator+=(rational CR x) {
    T g = (T)gcd(den, x.den);
    num = num * (x.den / g) + x.num * (den /= g), g = (T)gcd(num, g);
    num /= g, den *= x.den / g;
    return *this;
  }
  CEXP rational &operator-=(rational CR x) {
    T g = (T)gcd(den, x.den);
    num = num * (x.den / g) - x.num * (den /= g), g = (T)gcd(num, g);
    num /= g, den *= x.den / g;
    return *this;
  }
  CEXP rational &operator*=(rational CR x) {
    const T g1 = (T)gcd(num, x.den), g2 = (T)gcd(x.num, den);
    num = num / g1 * (x.num / g2), den = den / g2 * (x.den / g1);
    return *this;
  }
  CEXP rational &operator/=(rational CR x) {
    const T g1 = (T)gcd(num, x.num), g2 = (T)gcd(den, x.den);
    num = num / g1 * (x.den / g2), den = den / g2 * (x.num / g1);
    if CEXP (std::is_signed_v<T>)
      if (den < 0) num = -num, den = -den;
    return *this;
  }
  friend CEXP rational operator+(rational x, T y) { return x += y; }
  friend CEXP rational operator-(rational x, T y) { return x -= y; }
  friend CEXP rational operator*(rational x, T y) { return x *= y; }
  friend CEXP rational operator/(rational x, T y) { return x /= y; }
  friend CEXP rational operator+(rational x, rational CR y) { return x += y; }
  friend CEXP rational operator-(rational x, rational CR y) { return x -= y; }
  friend CEXP rational operator*(rational x, rational CR y) { return x *= y; }
  friend CEXP rational operator/(rational x, rational CR y) { return x /= y; }
  CEXP rational operator+() const { return *this; }
  CEXP rational operator-() const { return rational(-num, den); }
  CEXP rational &operator++() {
    num += den;
    return *this;
  }
  CEXP rational &operator--() {
    num -= den;
    return *this;
  }
  friend CEXP int operator<=>(rational CR x, rational CR y) {
    const auto _ = (x - y).num;
    return _ < 0 ? -1 : _ > 0;
  }
  friend CEXP bool operator==(rational CR x, rational CR y) { return x.num == y.num && x.den == y.den; }
  friend std::istream &operator>>(std::istream &is, rational &x) { return is >> x.num >> x.den; }
  friend std::ostream &operator<<(std::ostream &os, rational CR x) { return os << x.num << ' ' << x.den; }

  template <arithm_c U>
  CEXP U convert_to() const { return U(num) / U(den); }
};

}  // namespace tifa_libs::math

#endif