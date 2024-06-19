#ifndef TIFALIBS_GEO3D_SDIST3_PLP
#define TIFALIBS_GEO3D_SDIST3_PLP

#include "planev.hpp"
#include "point3d.hpp"

namespace tifa_libs::geo {

template <class FP>
CEXP FP sdist3_PlP(planev<FP> pl, point3d<FP> CR p) { return (p - *pl.u) * pl.normal() / pl.normal().norm(); }

}  // namespace tifa_libs::geo

#endif