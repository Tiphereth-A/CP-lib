#ifndef TIFALIBS_POLY_LN
#define TIFALIBS_POLY_LN

#include "poly_deriv.hpp"
#include "poly_int.hpp"
#include "poly_inv.hpp"

namespace tifa_libs::math {

template <class T>
inline poly<T> poly_ln(poly<T> const &p, size_t n = 0) {
  assert(p[0] == 1);
  if (!n) n = p.size();
  auto _ = poly_deriv(p).pre(n);
  _.conv(poly_inv(p, n));
  return poly_int(_).pre(n);
}

}  // namespace tifa_libs::math

#endif