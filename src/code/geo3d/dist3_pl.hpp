#ifndef TIFALIBS_GEO3D_DIST3_PL
#define TIFALIBS_GEO3D_DIST3_PL

#include "line3d.hpp"
#include "point3d.hpp"

namespace tifa_libs::geo {

template <class FP>
CEXP FP dist3_PL(cT_(point3d<FP>) p, cT_(line3d<FP>) l) { return ((l.r - l.l) / (p - l.l)).norm() / (l.r - l.l).norm(); }

}  // namespace tifa_libs::geo

#endif