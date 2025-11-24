#ifndef TIFALIBS_MATH_EINT
#define TIFALIBS_MATH_EINT

#include "../util/traits_others.hpp"

namespace tifa_libs::math {

template <class T>
class eint {
  T r_, i_;

 public:
  // $\omega$, $\omega^2$
  // $1+\omega+\omega^2=0$
  const static inline eint<T> w{0, 1}, w2{-T(1), -T(1)};

  CEXP eint(cT_(T) real = T{}, cT_(T) imag = T{}) NE : r_(real), i_(imag) {}

  CEXP T CR real() CNE { return r_; }
  CEXP T CR imag() CNE { return i_; }
  CEXP T norm() CNE { return r_ * (r_ - i_) + i_ * i_; }
  CEXP T& real() NE { return r_; }
  CEXP T& imag() NE { return i_; }
  CEXP void real(cT_(T) x) NE { r_ = x; }
  CEXP void imag(cT_(T) x) NE { i_ = x; }
  CEXP eint& operator+=(cT_(T) x) NE {
    r_ += x;
    return *this;
  }
  CEXP eint& operator-=(cT_(T) x) NE {
    r_ -= x;
    return *this;
  }
  CEXP eint& operator*=(cT_(T) x) NE {
    r_ *= x, i_ *= x;
    return *this;
  }
  CEXP eint& operator+=(eint CR x) NE {
    r_ += x.real(), i_ += x.imag();
    return *this;
  }
  CEXP eint& operator-=(eint CR x) NE {
    r_ -= x.real(), i_ -= x.imag();
    return *this;
  }
  CEXP eint& operator*=(eint CR x) NE {
    T _ = r_;
    r_ = r_ * x.real() - i_ * x.imag(), i_ = i_ * x.real() + _ * x.imag() - i_ * x.imag();
    return *this;
  }
  friend CEXP eint operator+(eint x, cT_(T) y) NE { return x += y; }
  friend CEXP eint operator-(eint x, cT_(T) y) NE { return x -= y; }
  friend CEXP eint operator*(eint x, cT_(T) y) NE { return x *= y; }
  friend CEXP eint operator+(eint x, eint CR y) NE { return x += y; }
  friend CEXP eint operator-(eint x, eint CR y) NE { return x -= y; }
  friend CEXP eint operator*(eint x, eint CR y) NE { return x *= y; }
  CEXP eint operator+() CNE { return *this; }
  CEXP eint operator-() CNE { return eint(-r_, -i_); }
  friend CEXP T norm(eint CR x) NE { return x.norm(); }
  friend CEXP eint conj(eint CR x) NE { return eint{x.r_ - x.i_, -x.i_}; }
  friend CEXP bool operator==(eint CR x, eint CR y) NE { return x.real() == y.real() && x.imag() == y.imag(); }
  friend auto& operator>>(istream_c auto& is, eint& x) NE { return is >> x.r_ >> x.i_; }
  friend auto& operator<<(ostream_c auto& os, eint CR x) NE { return os << x.real() << ' ' << x.imag(); }
};

}  // namespace tifa_libs::math

#endif