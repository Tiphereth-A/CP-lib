#ifndef TIFA_LIBS_GEO2D_SAREA_CT
#define TIFA_LIBS_GEO2D_SAREA_CT

#include "circle.hpp"
#include "util.hpp"

namespace tifa_libs::geo2d {

// area of intersection of circle and triangle
//! WITH DIRECTION, sgn is cross(c.o, p1, p2)
//! the center ot circle is also a endpoint of triangle
template <class FP>
FP sarea_CT(circle<FP> const &c, point<FP> const &p1, point<FP> const &p2) {
  if (is_zero(cross(c.o, p1, p2))) return FP{};
  vec<point<FP>> is = ins_CL(c, {p1, p2});
  if (is.empty()) return c.area(ang_PP(p1 - c.o, p2 - c.o));
  bool b1 = is_ge(dist_PP(p1, c.o), c.r), b2 = is_ge(dist_PP(p2, c.o), c.r);
  if (b1 && b2) {
    FP res = c.area(ang_PP(p1 - c.o, p2 - c.o));
    if (!is_pos(dot(is[0], p1, p2))) res -= c.crown_area(ang_PP(is[0] - c.o, is[1] - c.o));
    return res;
  }
  if (b1) return c.area(ang_PP(p1 - c.o, is[0] - c.o)) + cross(c.o, is[0], p2) / 2;
  if (b2) return c.area(ang_PP(is[1] - c.o, p2 - c.o)) + cross(c.o, p1, is[1]) / 2;
  return cross(c.o, p1, p2) / 2;
}

}  // namespace tifa_libs::geo2d

#endif