#ifndef TIFALIBS_GEO2D_DOT
#define TIFALIBS_GEO2D_DOT

#include "point.hpp"

namespace tifa_libs::geo {

// (a - o) * (b - o)
template <class FP>
CEXP FP dot(point<FP> CR o, point<FP> CR a, point<FP> CR b) { return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y); }
template <class FP>
CEXP int sgn_dot(point<FP> CR o, point<FP> CR a, point<FP> CR b) { return sgn(dot(o, a, b)); }

}  // namespace tifa_libs::geo

#endif