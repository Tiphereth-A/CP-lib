#ifndef TIFA_LIBS_GEO3D_PLANE
#define TIFA_LIBS_GEO3D_PLANE

#include "point3d.hpp"

namespace tifa_libs::geo {

template <class FP>
struct plane {
  point3d<FP> u, v, w;
  constexpr plane(point3d<FP> const &a, point3d<FP> const &b, point3d<FP> const &c) : u(a), v(b), w(c) {}

  friend std::istream &operator>>(std::istream &is, plane &pl) { return is >> pl.u >> pl.v >> pl.w; }
  friend std::ostream &operator<<(std::ostream &os, plane const &pl) { return os << pl.u << ' ' << pl.v << ' ' << pl.w; }

  point3d<FP> normal() const { return (v - u) ^ (w - u); }
  FP area() const { return normal().norm() / 2; }

  point3d<FP> &get(usz i) {
    if (i == 0) return u;
    if (i == 1) return v;
    if (i == 2) return w;
  }
  point3d<FP> get(usz i) const {
    if (i == 0) return u;
    if (i == 1) return v;
    if (i == 2) return w;
  }
};

}  // namespace tifa_libs::geo

#endif