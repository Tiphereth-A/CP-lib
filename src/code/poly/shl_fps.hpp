#ifndef TIFALIBS_POLY_SHL_FPS
#define TIFALIBS_POLY_SHL_FPS

#include "poly.hpp"

namespace tifa_libs::math {

template <template <class... Ts> class ccore, class mint, class... args>
CEXP auto shl_fps(poly<ccore, mint, args...> CR p, usz x) NE {
  if (!x) return p;
  auto _ = p;
  if (x >= _.size()) {
    std::ranges::fill(_, 0);
    return _;
  }
  std::fill(_.begin(), std::move_backward(_.begin(), std::prev(_.end(), (isz)x), _.end()), 0);
  return _;
}

}  // namespace tifa_libs::math

#endif