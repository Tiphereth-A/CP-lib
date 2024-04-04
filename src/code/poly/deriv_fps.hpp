#ifndef TIFALIBS_POLY_DERIV_FPS
#define TIFALIBS_POLY_DERIV_FPS

#include "poly.hpp"

namespace tifa_libs::math {

template <class mint, class ccore>
constexpr poly<mint, ccore> deriv_fps(poly<mint, ccore> const &p) {
  auto _ = p;
  for (u32 i = 1; i < _.size(); ++i) _[i - 1] = _[i] * i;
  _.data().back() = 0;
  return _;
}

}  // namespace tifa_libs::math

#endif