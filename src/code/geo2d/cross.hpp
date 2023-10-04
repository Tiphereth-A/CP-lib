#ifndef TIFA_LIBS_GEO2D_CROSS
#define TIFA_LIBS_GEO2D_CROSS

#include "point.hpp"

namespace tifa_libs::geo2d {

// (p2 - p1) ^  (p3 - p1)
template <class FP>
constexpr FP cross(point<FP> const &p1, point<FP> const &p2, point<FP> const &p3) { return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y); }
template <class FP>
constexpr int sgn_cross(point<FP> const &p1, point<FP> const &p2, point<FP> const &p3) { return sgn(cross(p1, p2, p3)); }

}  // namespace tifa_libs::geo2d

#endif