#ifndef TIFALIBS_GEO3D_LINE3D
#define TIFALIBS_GEO3D_LINE3D

#include "point3d.hpp"

namespace tifa_libs::geo {

template <class FP>
struct line3d {
  point3d<FP> l, r;
  explicit CEXP line3d(cT_(point3d<FP>) s, cT_(point3d<FP>) t) : l(s), r(t) {}

  friend std::istream &operator>>(std::istream &is, line3d &l) { return is >> l.l >> l.r; }
  friend std::ostream &operator<<(std::ostream &os, line3d CR l) { return os << l.l << ' ' << l.r; }
};

}  // namespace tifa_libs::geo

#endif