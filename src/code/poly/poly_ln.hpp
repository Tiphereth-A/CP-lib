#ifndef TIFALIBS_POLY_LN
#define TIFALIBS_POLY_LN

#include "poly_deriv.hpp"
#include "poly_int.hpp"
#include "poly_inv.hpp"

namespace tifa_libs::math {

template <class T>
inline poly<T> poly_ln(poly<T> const &p) {
  assert(p[0] == 1);
  size_t n = p.size();
  auto _ = poly_deriv(p);
  _.conv(poly_inv(p));
  _ = poly_int(_);
  _.resize(n);
  return _;
}

}  // namespace tifa_libs::math

#endif