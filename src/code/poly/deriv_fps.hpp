#ifndef TIFALIBS_POLY_DERIV_FPS
#define TIFALIBS_POLY_DERIV_FPS

#include "poly.hpp"

namespace tifa_libs::math {

template <template <class... Ts> class ccore, class mint, class... args>
CEXP auto deriv_fps(poly<ccore, mint, args...> CR p) NE {
  auto _ = p;
  flt_ (u32, i, 1, (u32)_.size()) _[i - 1] = _[i] * i;
  _.back() = 0;
  return _;
}

}  // namespace tifa_libs::math

#endif