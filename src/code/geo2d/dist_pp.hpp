#ifndef TIFALIBS_GEO2D_DIST_PP
#define TIFALIBS_GEO2D_DIST_PP

#include "point.hpp"

namespace tifa_libs::geo {

// distance of two points (Euclidian)
template <class FP>
CEXP FP dist_PP(point<FP> CR p1, point<FP> CR p2) { return (p1 - p2).norm(); }

}  // namespace tifa_libs::geo

#endif