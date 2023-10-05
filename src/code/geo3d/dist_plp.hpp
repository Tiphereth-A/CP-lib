#ifndef TIFA_LIBS_GEO3D_DIST_PLP
#define TIFA_LIBS_GEO3D_DIST_PLP

#include "plane.hpp"
#include "point3d.hpp"

namespace tifa_libs::geo {

template <class FP>
constexpr FP dist_PlP(plane<FP> const &pl, point3d<FP> const &p) {return (p - pl.u) * pl.normal() / pl.normal().norm(); }

}  // namespace tifa_libs::geo

#endif