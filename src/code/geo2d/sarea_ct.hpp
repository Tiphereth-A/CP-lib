#ifndef TIFALIBS_GEO2D_SAREA_CT
#define TIFALIBS_GEO2D_SAREA_CT

#include "ang_pp.hpp"
#include "dot.hpp"
#include "ins_cl.hpp"

namespace tifa_libs::geo {

// area of intersection of circle and triangle
//! WITH DIRECTION, sgn is cross(c.o, p1, p2)
//! the center ot circle is also a endpoint of triangle
template <class FP>
CEXP FP sarea_CT(circle<FP> CR c, point<FP> CR p1, point<FP> CR p2) NE {
  if (is_zero(cross(c.o, p1, p2))) return FP{};
  const auto is = ins_CL(c, {p1, p2});
  if (!is.has_value()) return c.area(ang_PP(p1 - c.o, p2 - c.o));
  bool b1 = is_gt(dist_PP(p1, c.o), c.r), b2 = is_gt(dist_PP(p2, c.o), c.r);
  if (b1 && b2) {
    FP res = c.area(ang_PP(p1 - c.o, p2 - c.o));
    if (!is_pos(dot(is.value().first, p1, p2))) res -= c.crown_area(ang_PP(is.value().first - c.o, is.value().second - c.o));
    return res;
  }
  if (b1) return c.area(ang_PP(p1 - c.o, is.value().first - c.o)) + cross(c.o, is.value().first, p2) / 2;
  if (b2) return c.area(ang_PP(is.value().second - c.o, p2 - c.o)) + cross(c.o, p1, is.value().second) / 2;
  return cross(c.o, p1, p2) / 2;
}

}  // namespace tifa_libs::geo

#endif