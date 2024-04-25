#ifndef TIFALIBS_GEO2D_DIST_PP_MA
#define TIFALIBS_GEO2D_DIST_PP_MA

#include "point.hpp"

namespace tifa_libs::geo {

// distance of two points (Manhattan)
template <class FP>
CEXP FP dist_PP_Ma(point<FP> CR p1, point<FP> CR p2) { return abs(p1.x - p2.x) + abs(p1.y - p2.y); }

}  // namespace tifa_libs::geo

#endif