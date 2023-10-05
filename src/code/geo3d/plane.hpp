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
};

}  // namespace tifa_libs::geo

#endif