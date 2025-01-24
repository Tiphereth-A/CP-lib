#ifndef TIFALIBS_POLY_SHR_FPS
#define TIFALIBS_POLY_SHR_FPS

#include "poly.hpp"

namespace tifa_libs::math {

template <template <class... Ts> class ccore, class mint, class... args>
CEXP auto shr_fps(poly<ccore, mint, args...> CR p, usz x) NE {
  if (!x) return p;
  auto _ = p;
  if (x >= p.size()) {
    std::ranges::fill(_, 0);
    return _;
  }
  std::fill(std::move(_.begin() + (isz)x, _.end(), _.begin()), _.end(), 0);
  return _;
}
template <template <class... Ts> class ccore, class mint, class... args>
CEXP auto shr_strip_fps(poly<ccore, mint, args...> CR p, usz x) NE {
  auto _ = shr_fps(p, x);
  _.strip();
  return _;
}

}  // namespace tifa_libs::math

#endif