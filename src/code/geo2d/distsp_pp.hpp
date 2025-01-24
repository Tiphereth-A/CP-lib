#ifndef TIFALIBS_GEO2D_DISTSP_PP
#define TIFALIBS_GEO2D_DISTSP_PP

#include "point.hpp"

namespace tifa_libs::geo {

// distance of two points on sphere with radius %r (Euclidian)
template <class FP>
CEXP FP distsp_PP(FP r, point<FP> CR p1, point<FP> CR p2) NE { return r * std::acos(std::sin(p1.y) * std::sin(p2.y) + std::cos(p1.y) * std::cos(p2.y) * std::cos(p1.x - p2.x)); }

}  // namespace tifa_libs::geo

#endif