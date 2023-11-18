#ifndef TIFALIBS_POLY_DERIV
#define TIFALIBS_POLY_DERIV

#include "poly.hpp"

namespace tifa_libs::math {

template <class T>
poly<T> poly_deriv(poly<T> const &p) {
  auto _ = p;
  for (u32 i = 1; i < _.size(); ++i) _[i - 1] = _[i] * i;
  _.data().back() = 0;
  return _;
}

}  // namespace tifa_libs::math

#endif