#ifndef TIFA_LIBS_GEO2D_DIST_PP
#define TIFA_LIBS_GEO2D_DIST_PP

#include "point.hpp"

namespace tifa_libs::geo {

// distance of two points (Euclidian)
template <class FP>
constexpr FP dist_PP(point<FP> const &p1, point<FP> const &p2) { return (p1 - p2).norm(); }

}  // namespace tifa_libs::geo

#endif