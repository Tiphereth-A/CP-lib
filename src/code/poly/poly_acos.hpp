#ifndef TIFALIBS_POLY_ACOS
#define TIFALIBS_POLY_ACOS

#include "poly_deriv.hpp"
#include "poly_int.hpp"
#include "poly_inv.hpp"
#include "poly_sqrt.hpp"

namespace tifa_libs::math {

template <class T>
inline poly<T> poly_acos(poly<T> const &p) {
  usz n = p.size();
  poly<T> _ = -p;
  _.conv(p);
  _.resize(n);
  _ = -poly_inv(poly_sqrt(_ + 1));
  _.conv(poly_deriv(p));
  _.resize(n);
  return poly_int(_);
}

}  // namespace tifa_libs::math

#endif