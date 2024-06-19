#ifndef TIFALIBS_GEO3D_DIST3_PP
#define TIFALIBS_GEO3D_DIST3_PP

#include "point3d.hpp"

namespace tifa_libs::geo {

template <class FP>
CEXP FP dist3_PP(point3d<FP> CR a, point3d<FP> CR b) { return (a - b).norm(); }

}  // namespace tifa_libs::geo

#endif