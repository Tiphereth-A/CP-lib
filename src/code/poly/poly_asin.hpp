#ifndef TIFALIBS_POLY_ASIN
#define TIFALIBS_POLY_ASIN

#include "poly_deriv.hpp"
#include "poly_int.hpp"
#include "poly_inv.hpp"
#include "poly_sqrt.hpp"

namespace tifa_libs::math {

template <class T>
inline poly<T> poly_asin(poly<T> const &p) {
  size_t n = p.size();
  poly<T> _ = -p;
  _.conv(p, n);
  _[0] = _[0] + 1;
  _ = poly_inv(poly_sqrt(_));
  _.conv(poly_deriv(p), n);
  return poly_int(_);
}

}  // namespace tifa_libs::math

#endif