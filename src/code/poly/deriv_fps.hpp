#ifndef TIFALIBS_POLY_DERIV_FPS
#define TIFALIBS_POLY_DERIV_FPS

#include "poly.hpp"

namespace tifa_libs::math {

template <class mint, class ccore>
CEXP poly<mint, ccore> deriv_fps(poly<mint, ccore> CR p) {
  auto _ = p;
  flt_ (u32, i, 1, (u32)_.size()) _[i - 1] = _[i] * i;
  _.data().back() = 0;
  return _;
}

}  // namespace tifa_libs::math

#endif