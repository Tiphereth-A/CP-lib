#ifndef TIFA_LIBS_GEO2D_DIST_PP
#define TIFA_LIBS_GEO2D_DIST_PP

#include "point.hpp"

namespace tifa_libs::geo {

// distance of two points (Euclidian)
template <class FP>
constexpr FP dist_PP(point<FP> const &lhs, point<FP> const &rhs) { return (lhs - rhs).norm(); }

}  // namespace tifa_libs::geo

#endif