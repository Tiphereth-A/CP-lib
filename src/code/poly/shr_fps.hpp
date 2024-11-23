#ifndef TIFALIBS_POLY_SHR_FPS
#define TIFALIBS_POLY_SHR_FPS

#include "poly.hpp"

namespace tifa_libs::math {

template <template <class... Ts> class ccore, class mint, class... args>
CEXP auto shr_fps(poly<ccore, mint, args...> CR p, usz x) {
  if (!x) return p;
  if (auto _ = p; x >= p.size()) return std::ranges::fill(_, 0), _;
  else return std::fill(std::move(_.begin() + (isz)x, _.end(), _.begin()), _.end(), 0), _;
}
template <template <class... Ts> class ccore, class mint, class... args>
CEXP auto shr_strip_fps(poly<ccore, mint, args...> CR p, usz x) {
  auto _ = shr_fps(p, x);
  return _.strip(), _;
}

}  // namespace tifa_libs::math

#endif