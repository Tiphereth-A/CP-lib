#ifndef TIFALIBS_MATH_FRAC_ITV
#define TIFALIBS_MATH_FRAC_ITV

#include "rational.hpp"

namespace tifa_libs::math {

//! a < b
template <uint_c T>
CEXP rational<T> frac_itv(rational<T> a, rational<T> b) {
  T _ = a.num / a.den;
  a.num -= _ * a.den, b.num -= _ * b.den;
  if (b.num > b.den) return {1 + _, 1};
  auto x = frac_itv(rational<T>{b.den, b.num}, rational<T>{a.den, a.num});
  return {x.den + _ * x.num, x.num};
}

}  // namespace tifa_libs::math

#endif