#ifndef TIFALIBS_POLY_SHR_FPS
#define TIFALIBS_POLY_SHR_FPS

#include "poly.hpp"

namespace tifa_libs::math {

template <template <class... Ts> class ccore, class mint, class... args>
CEXP auto shr_fps(poly<ccore, mint, args...> CR p, usz x) NE {
  retif_((!x) [[unlikely]], p);
  auto _ = p;
  fill(std::shift_left(begin(_), end(_), (isz)x), end(_), 0);
  return _;
}
template <template <class... Ts> class ccore, class mint, class... args>
CEXP auto shr_strip_fps(poly<ccore, mint, args...> CR p, usz x) NE {
  auto _ = p;
  _.erase(std::shift_left(begin(_), end(_), (isz)x), end(_));
  return _;
}

}  // namespace tifa_libs::math

#endif