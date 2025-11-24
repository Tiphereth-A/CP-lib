#ifndef TIFALIBS_GEO3D_LINE3D
#define TIFALIBS_GEO3D_LINE3D

#include "point3d.hpp"

namespace tifa_libs::geo {

template <class FP>
struct line3d {
  point3d<FP> l, r;
  CEXP line3d(point3d<FP> CR s, point3d<FP> CR t) NE : l(s), r(t) {}

  friend auto& operator>>(istream_c auto& is, line3d& l) NE { return is >> l.l >> l.r; }
  friend auto& operator<<(ostream_c auto& os, line3d CR l) NE { return os << l.l << ' ' << l.r; }
};

}  // namespace tifa_libs::geo

#endif