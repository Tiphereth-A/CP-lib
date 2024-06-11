#ifndef TIFALIBS_GEO3D_POLYGON3D
#define TIFALIBS_GEO3D_POLYGON3D

#include "point3d.hpp"

namespace tifa_libs::geo {

template <class FP>
struct polygon3d {
  vec<point3d<FP>> vp;
  vec<pttu> vil;
  vec<pt3u> vip;

  CEXP explicit polygon3d(vec<point3d<FP>> CR points) : vp(points) {}

  CEXP void connect(u32 u, u32 v) { vil.emplace_back(u, v); }
  CEXP void connect(u32 u, u32 v, u32 w) { vip.emplace_back(u, v, w); }
};

}  // namespace tifa_libs::geo

#endif