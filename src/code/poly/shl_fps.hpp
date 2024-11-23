#ifndef TIFALIBS_POLY_SHL_FPS
#define TIFALIBS_POLY_SHL_FPS

#include "poly.hpp"

namespace tifa_libs::math {

template <template <class... Ts> class ccore, class mint, class... args>
CEXP auto shl_fps(poly<ccore, mint, args...> CR p, usz x) {
  if (!x) return p;
  if (auto _ = p; x >= _.size()) return std::ranges::fill(_, 0), _;
  else return std::fill(_.begin(), std::move_backward(_.begin(), std::prev(_.end(), (isz)x), _.end()), 0), _;
}

}  // namespace tifa_libs::math

#endif