#ifndef TIFALIBS_POLY_ATAN_FPS
#define TIFALIBS_POLY_ATAN_FPS

#include "deriv_fps.hpp"
#include "int_fps.hpp"
#include "inv_fps.hpp"

namespace tifa_libs::math {

template <class mint, class ccore>
CEXP poly<mint, ccore> atan_fps(poly<mint, ccore> CR p) {
  u32 n = p.size();
  auto _ = p;
  (_ *= _).resize(n);
  _[0] += 1;
  (_ = inv_fps(_) * deriv_fps(p)).resize(n);
  return int_fps(_);
}

}  // namespace tifa_libs::math

#endif