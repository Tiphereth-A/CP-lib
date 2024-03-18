#ifndef TIFALIBS_POLY_POLY_ATAN
#define TIFALIBS_POLY_POLY_ATAN

#include "poly_deriv.hpp"
#include "poly_int.hpp"
#include "poly_inv.hpp"

namespace tifa_libs::math {

template <class poly>
constexpr poly poly_atan(poly const &p) {
  u32 n = p.size();
  poly _ = p;
  _.conv(p);
  _.resize(n);
  _ = -poly_inv(_ + 1);
  _.conv(poly_deriv(p));
  _.resize(n);
  return poly_int(_);
}

}  // namespace tifa_libs::math

#endif