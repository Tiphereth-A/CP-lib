#ifndef TIFALIBS_GEO3D_DIST3_PL
#define TIFALIBS_GEO3D_DIST3_PL

#include "line3d.hpp"
#include "point3d.hpp"

namespace tifa_libs::geo {

template <class FP>
constexpr FP dist3_PL(point3d<FP> const &p, line3d<FP> const &l) { return ((l.r - l.l) / (p - l.l)).norm() / (l.r - l.l).norm(); }

}  // namespace tifa_libs::geo

#endif