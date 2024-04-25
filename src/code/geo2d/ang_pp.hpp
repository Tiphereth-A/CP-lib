#ifndef TIFALIBS_GEO2D_ANG_PP
#define TIFALIBS_GEO2D_ANG_PP

#include "point.hpp"

namespace tifa_libs::geo {

// clamp angle of two points
template <class FP>
CEXP FP ang_PP(point<FP> CR p1, point<FP> CR p2) { return std::atan2(p1 ^ p2, p1 * p2); }

}  // namespace tifa_libs::geo

#endif