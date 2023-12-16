#ifndef TIFALIBS_GEO2D_ANG2PI_PP
#define TIFALIBS_GEO2D_ANG2PI_PP

#include "ang_pp.hpp"

namespace tifa_libs::geo {

// clamp angle of two points, result in [0,2 pi)
template <class FP>
constexpr FP ang2pi_PP(point<FP> const &p1, point<FP> const &p2) {
  FP res = ang_PP(p1, p2);
  return is_neg(res) ? res + 2 * pi_v<FP> : res;
}

}  // namespace tifa_libs::geo

#endif