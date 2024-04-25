#ifndef TIFALIBS_GEO2D_DIST_PP_CH
#define TIFALIBS_GEO2D_DIST_PP_CH

#include "point.hpp"

namespace tifa_libs::geo {

// distance of two points (Chebyshev)
template <class FP>
CEXP FP dist_PP_Ch(point<FP> CR p1, point<FP> CR p2) { return max(abs(p1.x - p2.x), abs(p1.y - p2.y)); }

}  // namespace tifa_libs::geo

#endif