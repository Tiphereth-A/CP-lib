#ifndef TIFALIBS_GEO3D_PLANE
#define TIFALIBS_GEO3D_PLANE

#include "point3d.hpp"

namespace tifa_libs::geo {

template <class FP>
struct plane {
  point3d<FP> u, v, w;
  CEXP plane(cT_(point3d<FP>) a, cT_(point3d<FP>) b, cT_(point3d<FP>) c) : u(a), v(b), w(c) {}

  friend std::istream &operator>>(std::istream &is, plane &pl) { return is >> pl.u >> pl.v >> pl.w; }
  friend std::ostream &operator<<(std::ostream &os, plane CR pl) { return os << pl.u << ' ' << pl.v << ' ' << pl.w; }

  CEXP point3d<FP> normal() const { return (v - u) ^ (w - u); }
  CEXP FP area() const { return normal().norm() / 2; }

  CEXP point3d<FP> &get(u32 i) {
    if (i == 0) return u;
    if (i == 1) return v;
    if (i == 2) return w;
  }
  CEXP point3d<FP> get(u32 i) const {
    if (i == 0) return u;
    if (i == 1) return v;
    if (i == 2) return w;
  }
};

}  // namespace tifa_libs::geo

#endif