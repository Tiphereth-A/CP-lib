#ifndef TIFALIBS_GEO2D_DIST_PP
#define TIFALIBS_GEO2D_DIST_PP

#include "point.hpp"

namespace tifa_libs::geo {

// distance of two points (Manhattan)
template <class FP>
CEXP FP dist_PP_Ma(point<FP> CR p1, point<FP> CR p2) { return abs(p1.x - p2.x) + abs(p1.y - p2.y); }
// distance of two points (Euclidian)
template <class FP>
CEXP FP dist_PP(point<FP> CR p1, point<FP> CR p2) { return (p1 - p2).norm(); }
// distance of two points (Chebyshev)
template <class FP>
CEXP FP dist_PP_Ch(point<FP> CR p1, point<FP> CR p2) { return max(abs(p1.x - p2.x), abs(p1.y - p2.y)); }

}  // namespace tifa_libs::geo

#endif