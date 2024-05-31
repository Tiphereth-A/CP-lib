#ifndef TIFALIBS_GEO2D_ANG_PP
#define TIFALIBS_GEO2D_ANG_PP

#include "point.hpp"

namespace tifa_libs::geo {

// clamp angle of two points, result in $(-\pi,\pi]$
template <class FP>
CEXP FP ang_PP(point<FP> CR p1, point<FP> CR p2) { return std::atan2(p1 ^ p2, p1 * p2); }
// clamp angle of two points, result in $[0,2\pi)$
template <class FP>
CEXP FP ang2pi_PP(point<FP> CR p1, point<FP> CR p2) {
  const FP res = ang_PP(p1, p2);
  return is_neg(res) ? res + 2 * pi_v<FP> : res;
}

}  // namespace tifa_libs::geo

#endif