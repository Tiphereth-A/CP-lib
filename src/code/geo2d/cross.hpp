#ifndef TIFALIBS_GEO2D_CROSS
#define TIFALIBS_GEO2D_CROSS

#include "point.hpp"

namespace tifa_libs::geo {

// (a - o) ^ (b - o)
template <class FP>
CEXP FP cross(point<FP> CR o, point<FP> CR a, point<FP> CR b) { return (a.x - o.x) * (b.y - o.y) - (b.x - o.x) * (a.y - o.y); }
template <std::floating_point FP>
CEXP FP cross_unit(point<FP> CR o, point<FP> CR a, point<FP> CR b) { return (a - o).do_unit() ^ (b - o).do_unit(); }
template <std::floating_point FP>
CEXP int sgn_cross(point<FP> CR o, point<FP> CR a, point<FP> CR b) { return sgn(cross_unit(o, a, b)); }
template <class FP>
CEXP int sgn_cross(point<FP> CR o, point<FP> CR a, point<FP> CR b) { return sgn(cross(o, a, b)); }

}  // namespace tifa_libs::geo

#endif