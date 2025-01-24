#ifndef TIFALIBS_MATH_GINT
#define TIFALIBS_MATH_GINT

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class T, i64 M>
class gint {
  T r_, i_;

 public:
  CEXP gint(cT_(T) real = T{}, cT_(T) imag = T{}) NE : r_(real), i_(imag) {}

  CEXP T CR real() CNE { return r_; }
  CEXP T CR imag() CNE { return i_; }
  CEXP T norm() CNE { return r_ * r_ - i_ * i_ * M; }
  CEXP T &real() NE { return r_; }
  CEXP T &imag() NE { return i_; }
  CEXP void real(cT_(T) x) NE { r_ = x; }
  CEXP void imag(cT_(T) x) NE { i_ = x; }
  CEXP gint &operator+=(cT_(T) x) NE {
    r_ += x;
    return *this;
  }
  CEXP gint &operator-=(cT_(T) x) NE {
    r_ -= x;
    return *this;
  }
  CEXP gint &operator*=(cT_(T) x) NE {
    r_ *= x, i_ *= x;
    return *this;
  }
  CEXP gint &operator/=(cT_(T) x) NE {
    r_ /= x, i_ /= x;
    return *this;
  }
  CEXP gint &operator+=(gint CR x) NE {
    r_ += x.real(), i_ += x.imag();
    return *this;
  }
  CEXP gint &operator-=(gint CR x) NE {
    r_ -= x.real(), i_ -= x.imag();
    return *this;
  }
  CEXP gint &operator*=(gint CR x) NE {
    const T _ = r_ * x.real() + i_ * x.imag() * M;
    i_ = r_ * x.imag() + i_ * x.real(), r_ = _;
    return *this;
  }
  CEXP gint &operator/=(gint CR x) NE {
    const T _ = r_ * x.real() - i_ * x.imag() * M, n_ = x.norm();
    if CEXP (std::is_integral_v<T>) {
      auto div = [](T x, T y) NE { const T a = x * 2 + y, b = y * 2; return a / b - (a % b < 0); };
      i_ = div(i_ * x.real() - r_ * x.imag(), n_), r_ = div(_, n_);
    } else i_ = (i_ * x.real() - r_ * x.imag()) / n_, r_ = _ / n_;
    return *this;
  }
  CEXP gint &operator%=(gint CR x) NE { return *this -= *this / x * x; }
  friend CEXP gint operator+(gint x, cT_(T) y) NE { return x += y; }
  friend CEXP gint operator-(gint x, cT_(T) y) NE { return x -= y; }
  friend CEXP gint operator*(gint x, cT_(T) y) NE { return x *= y; }
  friend CEXP gint operator/(gint x, cT_(T) y) NE { return x /= y; }
  friend CEXP gint operator+(gint x, gint CR y) NE { return x += y; }
  friend CEXP gint operator-(gint x, gint CR y) NE { return x -= y; }
  friend CEXP gint operator*(gint x, gint CR y) NE { return x *= y; }
  friend CEXP gint operator/(gint x, gint CR y) NE { return x /= y; }
  friend CEXP gint operator%(gint x, gint CR y) NE { return x %= y; }
  CEXP gint operator+() CNE { return *this; }
  CEXP gint operator-() CNE { return gint(-r_, -i_); }
  friend CEXP gint conj(gint CR x) NE { return gint{x.r_, -x.i_}; }
  friend CEXP T norm(gint CR x) NE { return x.norm(); }
  friend CEXP gint gcd(gint m, gint n) NE {
    while (n != gint{}) swap(m %= n, n);
    return m;
  }
  friend CEXP bool operator==(gint CR x, gint CR y) NE { return x.real() == y.real() && x.imag() == y.imag(); }
  friend std::istream &operator>>(std::istream &is, gint &x) NE { return is >> x.r_ >> x.i_; }
  friend std::ostream &operator<<(std::ostream &os, gint CR x) NE { return os << x.real() << ' ' << x.imag(); }
};

}  // namespace tifa_libs::math

#endif