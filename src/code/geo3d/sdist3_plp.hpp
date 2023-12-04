#ifndef TIFALIBS_GEO3D_SDIST3_PLP
#define TIFALIBS_GEO3D_SDIST3_PLP

#include "plane.hpp"
#include "point3d.hpp"

namespace tifa_libs::geo {

template <class FP>
constexpr FP sdist3_PlP(plane<FP> const &pl, point3d<FP> const &p) { return (p - pl.u) * pl.normal() / pl.normal().norm(); }

}  // namespace tifa_libs::geo

#endif