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
  auto _ = p;
  return poly_int(poly_deriv(p).conv(poly_inv(p), n));
}

}  // namespace tifa_libs::math

#endif