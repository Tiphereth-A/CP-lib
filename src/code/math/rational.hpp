#ifndef TIFALIBS_MATH_RATIONAL
#define TIFALIBS_MATH_RATIONAL

#include "../nt/gcd.hpp"

namespace tifa_libs::math {

template <int_c T>
class rational {
  T num, den;

 public:
  constexpr explicit rational(T numerator = 0, T denominator = 1) : num(numerator), den(denominator) {
    assert(den != 0);
    if (num == 0) den = 1;
    else {
      T g = gcd(num, den);
      num /= g, den /= g;
      if constexpr (std::is_signed_v<T>)
        if (den < 0) num = -num, den = -den;
    }
  }

  constexpr T const &numerator() const { return num; }
  constexpr T const &denominator() const { return den; }
  constexpr T &numerator() { return num; }
  constexpr T &denominator() { return den; }
  constexpr void numerator(T x) { num = x; }
  constexpr void denominator(T x) { den = x; }
  constexpr rational &operator+=(T x) {
    num += x * den;
    return *this;
  }
  constexpr rational &operator-=(T x) {
    num -= x * den;
    return *this;
  }
  constexpr rational &operator*=(T x) {
    T g = gcd(x, den);
    num *= x / g, den /= g;
    return *this;
  }
  constexpr rational &operator/=(T x) {
    assert(x);
    T g = gcd(x, num);
    num /= g, den *= x / g;
    if constexpr (std::is_signed_v<T>)
      if (den < 0) num = -num, den = -den;
    return *this;
  }
  constexpr rational &operator+=(rational const &x) {
    T g = gcd(den, x.den);
    num = num * (x.den / g) + x.num * (den /= g), g = gcd(num, g);
    num /= g, den *= x.den / g;
    return *this;
  }
  constexpr rational &operator-=(rational const &x) {
    T g = gcd(den, x.den);
    num = num * (x.den / g) - x.num * (den /= g), g = gcd(num, g);
    num /= g, den *= x.den / g;
    return *this;
  }
  constexpr rational &operator*=(rational const &x) {
    T g1 = gcd(num, x.den), g2 = gcd(x.num, den);
    num = num / g1 * (x.num / g2), den = den / g2 * (x.den / g1);
    return *this;
  }
  constexpr rational &operator/=(rational const &x) {
    T g1 = gcd(num, x.num), g2 = gcd(den, x.den);
    num = num / g1 * (x.den / g2), den = den / g2 * (x.num / g1);
    if constexpr (std::is_signed_v<T>)
      if (den < 0) num = -num, den = -den;
    return *this;
  }
  friend constexpr rational operator+(rational x, T y) { return x += y; }
  friend constexpr rational operator-(rational x, T y) { return x -= y; }
  friend constexpr rational operator*(rational x, T y) { return x *= y; }
  friend constexpr rational operator/(rational x, T y) { return x /= y; }
  friend constexpr rational operator+(rational x, rational const &y) { return x += y; }
  friend constexpr rational operator-(rational x, rational const &y) { return x -= y; }
  friend constexpr rational operator*(rational x, rational const &y) { return x *= y; }
  friend constexpr rational operator/(rational x, rational const &y) { return x /= y; }
  constexpr rational operator+() const { return *this; }
  constexpr rational operator-() const { return rational(-num, den); }
  constexpr rational &operator++() {
    num += den;
    return *this;
  }
  constexpr rational &operator--() {
    num -= den;
    return *this;
  }
  friend constexpr int operator<=>(rational const &x, rational const &y) {
    auto _ = (x - y).num;
    return _ < 0 ? -1 : _ > 0;
  }
  friend constexpr bool operator==(rational const &x, rational const &y) { return x.num == y.num && x.den == y.den; }
  friend std::istream &operator>>(std::istream &is, rational &x) { return is >> x.num >> x.den; }
  friend std::ostream &operator<<(std::ostream &os, rational const &x) { return os << x.num << ' ' << x.den; }

  template <arithm_c U>
  constexpr U convert_to() const { return U(num) / U(den); }
};

}  // namespace tifa_libs::math

#endif