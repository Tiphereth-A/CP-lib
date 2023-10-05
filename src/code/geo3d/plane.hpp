#ifndef TIFA_LIBS_GEO3D_PLANE
#define TIFA_LIBS_GEO3D_PLANE

#include "point3d.hpp"

namespace tifa_libs::geo {

template <class FP>
struct plane {
  point3d<FP> a, b, c;
  constexpr plane(point3d<FP> const &a, point3d<FP> const &b, point3d<FP> const &c):
    a(a), b(b), c(c) {}

  friend std::istream &operator>>(std::istream &is, plane &pl) { return is >> pl.a >> pl.b >> pl.c; }
  friend std::ostream &operator<<(std::ostream &os, plane const &pl) { return os << pl.a << ' ' << pl.b << ' ' << pl.c; }

  point3d<FP> normal() const { return (b - a) ^ (c - a); }
};

}  // namespace tifa_libs::geo

#endif