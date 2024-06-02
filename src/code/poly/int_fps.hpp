#ifndef TIFALIBS_POLY_INT_FPS
#define TIFALIBS_POLY_INT_FPS

#include "poly.hpp"

namespace tifa_libs::math {

template <class mint, class ccore>
CEXP poly<mint, ccore> int_fps(poly<mint, ccore> CR p) {
  auto _ = p;
  for (u32 i = _.size() - 1; i; --i) _[i] = _[i - 1] * mint(i).inv();
  return _[0] = 0, _;
}

}  // namespace tifa_libs::math

#endif