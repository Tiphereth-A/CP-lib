#ifndef TIFALIBS_GEO2D_EXTAN_CC
#define TIFALIBS_GEO2D_EXTAN_CC

#include "circle.hpp"
#include "line.hpp"
#include "tan_cp.hpp"

namespace tifa_libs::geo {

// external tagante lines of 2 circles
// maybe duplicate
template <class FP>
CEXP auto extan_CC(circle<FP> CR c1, circle<FP> CR c2) NE {
  std::optional<ptt<line<FP>>> ret;
  if (is_eq(c1.o.x, c2.o.x) && is_eq(c1.o.y, c2.o.y)) return ret;
  if (is_eq(c1.r, c2.r)) {
    point dr = (c2.o - c1.o).do_unit().do_rot90() * c1.r;
    ret.emplace(line{c1.o + dr, c2.o + dr}, line{c1.o - dr, c2.o - dr});
    return ret;
  }
  const point p = (c2.o * c1.r - c1.o * c2.r) / (c1.r - c2.r);
  const auto ps = tan_CP(c1, p), qs = tan_CP(c2, p);
  if (!ps || !qs) return ret;
  // c1 counter-clock wise
  ret.emplace(line{ps->first, qs->first}, line{ps->second, qs->second});
  return ret;
}

}  // namespace tifa_libs::geo

#endif