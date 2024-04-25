#ifndef TIFALIBS_GEO2D_EXTAN_CC
#define TIFALIBS_GEO2D_EXTAN_CC

#include "circle.hpp"
#include "line.hpp"
#include "tan_cp.hpp"

namespace tifa_libs::geo {

// external tagante lines of 2 circles
// maybe duplicate
template <class FP>
CEXP std::optional<ptt<line<FP>>> extan_CC(circle<FP> CR c1, circle<FP> CR c2) {
  if (is_eq(c1.o.x, c2.o.x) && is_eq(c1.o.y, c2.o.y)) return {};
  if (is_eq(c1.r, c2.r)) {
    point dr = (c2.o - c1.o).do_unit().do_rot90() * c1.r;
    return ptt<line<FP>>{{c1.o + dr, c2.o + dr}, {c1.o - dr, c2.o - dr}};
  }
  point p = (c2.o * c1.r - c1.o * c2.r) / (c1.r - c2.r);
  auto ps = tan_CP(c1, p), qs = tan_CP(c2, p);
  if (!ps.has_value() || !qs.has_value()) return {};
  // c1 counter-clock wise
  return ptt<line<FP>>{{ps.value().first, qs.value().first}, {ps.value().second, qs.value().second}};
}

}  // namespace tifa_libs::geo

#endif