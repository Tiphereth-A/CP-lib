#ifndef TIFALIBS_MATH_RATIONAL
#define TIFALIBS_MATH_RATIONAL

#include "../nt/gcd.hpp"
#include "../util/traits_others.hpp"

namespace tifa_libs::math {

template <int_c T>
struct rational {
  T num, den;

  CEXP rational(T numerator = T(0), T denominator = T(1)) NE : num(numerator), den(denominator) {
    if (assert(den != 0); num == 0) den = 1;
    else {
      const T g = (T)gcd(num, den);
      if CEXP (num /= g, den /= g; std::is_signed_v<T>)
        if (den < 0) num = -num, den = -den;
    }
  }

  CEXP rational &operator+=(T x) NE {
    num += x * den;
    return *this;
  }
  CEXP rational &operator-=(T x) NE {
    num -= x * den;
    return *this;
  }
  CEXP rational &operator*=(T x) NE {
    const T g = (T)gcd(x, den);
    num *= x / g, den /= g;
    return *this;
  }
  CEXP rational &operator/=(T x) NE {
    assert(x);
    const T g = (T)gcd(x, num);
    if CEXP (num /= g, den *= x / g; std::is_signed_v<T>)
      if (den < 0) num = -num, den = -den;
    return *this;
  }
  CEXP rational &operator+=(rational CR x) NE {
    T g = (T)gcd(den, x.den);
    num = num * (x.den / g) + x.num * (den /= g);
    g = (T)gcd(num, g);
    num /= g, den *= x.den / g;
    return *this;
  }
  CEXP rational &operator-=(rational CR x) NE {
    T g = (T)gcd(den, x.den);
    num = num * (x.den / g) - x.num * (den /= g);
    g = (T)gcd(num, g);
    num /= g, den *= x.den / g;
    return *this;
  }
  CEXP rational &operator*=(rational CR x) NE {
    const T g1 = (T)gcd(num, x.den), g2 = (T)gcd(x.num, den);
    num = num / g1 * (x.num / g2);
    den = den / g2 * (x.den / g1);
    return *this;
  }
  CEXP rational &operator/=(rational CR x) NE {
    const T g1 = (T)gcd(num, x.num), g2 = (T)gcd(den, x.den);
    if CEXP (num = num / g1 * (x.den / g2), den = den / g2 * (x.num / g1); std::is_signed_v<T>)
      if (den < 0) num = -num, den = -den;
    return *this;
  }
  friend CEXP rational operator+(rational x, T y) NE { return x += y; }
  friend CEXP rational operator-(rational x, T y) NE { return x -= y; }
  friend CEXP rational operator*(rational x, T y) NE { return x *= y; }
  friend CEXP rational operator/(rational x, T y) NE { return x /= y; }
  friend CEXP rational operator+(rational x, rational CR y) NE { return x += y; }
  friend CEXP rational operator-(rational x, rational CR y) NE { return x -= y; }
  friend CEXP rational operator*(rational x, rational CR y) NE { return x *= y; }
  friend CEXP rational operator/(rational x, rational CR y) NE { return x /= y; }
  CEXP rational operator+() CNE { return *this; }
  CEXP rational operator-() CNE { return rational(-num, den); }
  CEXP rational &operator++() NE {
    num += den;
    return *this;
  }
  CEXP rational &operator--() NE {
    num -= den;
    return *this;
  }
  friend CEXP int operator<=>(rational CR x, rational CR y) NE {
    const auto _ = (x - y).num;
    return _ < 0 ? -1 : _ > 0;
  }
  friend CEXP bool operator==(rational CR x, rational CR y) NE { return x.num == y.num && x.den == y.den; }
  friend auto &operator>>(istream_c auto &is, rational &x) NE { return is >> x.num >> x.den; }
  friend auto &operator<<(ostream_c auto &os, rational CR x) NE { return os << x.num << ' ' << x.den; }
  template <arithm_c U>
  CEXP U convert_to() CNE { return U(num) / U(den); }
};

}  // namespace tifa_libs::math

#endif