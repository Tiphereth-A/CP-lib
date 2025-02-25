#ifndef TIFALIBS_POLY_SHL_FPS
#define TIFALIBS_POLY_SHL_FPS

#include "poly.hpp"

namespace tifa_libs::math {

template <template <class... Ts> class ccore, class mint, class... args>
CEXP auto shl_fps(poly<ccore, mint, args...> CR p, usz x) NE {
  if (!x) return p;
  auto _ = p;
  fill(_.begin(), std::shift_right(_.begin(), _.end(), (isz)x), 0);
  return _;
}

}  // namespace tifa_libs::math

#endif