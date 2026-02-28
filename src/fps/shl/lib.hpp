#ifndef TIFALIBS_FPS_SHL_LIB
#define TIFALIBS_FPS_SHL_LIB

#include "../ds/poly/lib.hpp"

namespace tifa_libs::math {

template <template <class... Ts> class ccore, class mint, class... args>
CEXP auto shl_fps(poly<ccore, mint, args...> CR p, usz x) NE {
  retif_((!x) [[unlikely]], p);
  auto _ = p;
  fill(begin(_), std::shift_right(begin(_), end(_), (isz)x), 0);
  return _;
}

}  // namespace tifa_libs::math

#endif