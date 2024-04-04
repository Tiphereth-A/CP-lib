#ifndef TIFALIBS_POLY_INT_FPS
#define TIFALIBS_POLY_INT_FPS

#include "poly.hpp"

namespace tifa_libs::math {

template <class mint, class ccore>
constexpr poly<mint, ccore> int_fps(poly<mint, ccore> const &p) {
  auto _ = p;
  for (u32 i = _.size() - 1; i; --i) _[i] = _[i - 1] * mint(i).inv();
  _[0] = 0;
  return _;
}

}  // namespace tifa_libs::math

#endif