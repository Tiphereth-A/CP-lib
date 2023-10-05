#ifndef TIFA_LIBS_GEO2D_CROSS
#define TIFA_LIBS_GEO2D_CROSS

#include "point.hpp"

namespace tifa_libs::geo {

// (a - o) ^  (b - o)
template <class FP>
constexpr FP cross(point<FP> const &o, point<FP> const &a, point<FP> const &b) { return (a.x - o.x) * (b.y - o.y) - (b.x - o.x) * (a.y - o.y); }
template <class FP>
constexpr int sgn_cross(point<FP> const &o, point<FP> const &a, point<FP> const &b) { return sgn(cross(o, a, b)); }

}  // namespace tifa_libs::geo

#endif