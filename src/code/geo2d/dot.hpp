#ifndef TIFALIBS_GEO2D_DOT
#define TIFALIBS_GEO2D_DOT

#include "point.hpp"

namespace tifa_libs::geo {

// (a - o) * (b - o)
template <class FP>
constexpr FP dot(point<FP> const &o, point<FP> const &a, point<FP> const &b) { return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y); }
template <class FP>
constexpr int sgn_dot(point<FP> const &o, point<FP> const &a, point<FP> const &b) { return sgn(dot(o, a, b)); }

}  // namespace tifa_libs::geo

#endif