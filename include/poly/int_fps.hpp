#ifndef TIFALIBS_POLY_INT_FPS
#define TIFALIBS_POLY_INT_FPS

#include "poly.hpp"

namespace tifa_libs::math {

template <template <class... Ts> class ccore, class mint, class... args>
CEXP auto int_fps(poly<ccore, mint, args...> CR p) NE {
  auto _ = p;
  for (u32 i = (u32)_.size() - 1; i; --i) _[i] = _[i - 1] * mint(i).inv();
  _[0] = 0;
  return _;
}

}  // namespace tifa_libs::math

#endif