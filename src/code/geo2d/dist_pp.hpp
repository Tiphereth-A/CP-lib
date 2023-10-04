#ifndef TIFA_LIBS_GEO2D_DIST_PP
#define TIFA_LIBS_GEO2D_DIST_PP

#include "point.hpp"

namespace tifa_libs::geo2d {

// distance of two points (Euclidian)
template <class FP>
constexpr FP dist_PP(point<FP> const &lhs, point<FP> const &rhs) { return std::hypot(lhs.x - rhs.x, lhs.y - rhs.y); }

}  // namespace tifa_libs::geo2d

#endif