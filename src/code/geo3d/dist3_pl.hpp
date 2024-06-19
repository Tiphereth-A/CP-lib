#ifndef TIFALIBS_GEO3D_DIST3_PL
#define TIFALIBS_GEO3D_DIST3_PL

#include "../geo2d/cross.hpp"
#include "line3d.hpp"
#include "point3d.hpp"

namespace tifa_libs::geo {

template <class FP>
CEXP FP dist3_PL(point3d<FP> CR p, line3d<FP> CR l) { return cross(l.l, l.r, p).norm() / (l.r - l.l).norm(); }

}  // namespace tifa_libs::geo

#endif