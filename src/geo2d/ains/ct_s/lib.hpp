#pragma once

#include "../../ang_pp/lib.hpp"
#include "../../dis/pp_p/lib.hpp"
#include "../../dot/lib.hpp"
#include "../../ins/cl/lib.hpp"

namespace tifa_libs {

// area of intersection of circle and triangle
//! WITH DIRECTION, sgn is cross(c.o, p1, p2)
//! the center ot circle is also a endpoint of triangle
template <class FP>
CEXP FP sarea_CT(circle<FP> CR c, point<FP> CR p1, point<FP> CR p2) NE {
  if (is_zero(cross(c.o, p1, p2))) return FP{};
  const auto is = ins_CL(c, {p1, p2});
  if (!is) return c.area(ang_PP(p1 - c.o, p2 - c.o));
  bool b1 = comp_distp(p1, c.o, c.r) > 0, b2 = comp_distp(p2, c.o, c.r) > 0;
  if (b1 && b2) {
    FP res = c.area(ang_PP(p1 - c.o, p2 - c.o));
    if (!is_pos(dot(is->first, p1, p2))) res -= c.crown_area(ang_PP(is->first - c.o, is->second - c.o));
    return res;
  }
  if (b1) return c.area(ang_PP(p1 - c.o, is->first - c.o)) + cross(c.o, is->first, p2) / 2;
  if (b2) return c.area(ang_PP(is->second - c.o, p2 - c.o)) + cross(c.o, p1, is->second) / 2;
  return cross(c.o, p1, p2) / 2;
}

}  // namespace tifa_libs
