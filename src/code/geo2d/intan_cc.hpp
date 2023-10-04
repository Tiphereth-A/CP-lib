#ifndef TIFA_LIBS_GEO2D_INTAN_CC
#define TIFA_LIBS_GEO2D_INTAN_CC

#include "circle.hpp"
#include "line.hpp"
#include "tan_cp.hpp"

namespace tifa_libs::geo2d {

// internal tagante lines of 2 disjoint circles
// maybe 0, 2 (maybe duplicate)
template <class FP>
std::optional<ptt<line<FP>>> intan_CC(circle<FP> const &c1, circle<FP> const &c2) {
  if (is_eq(c1.o.x, c2.o.x) && is_eq(c1.o.y, c2.o.y)) return {};
  point p = (c1.o * c2.r + c2.o * c1.r) / (c1.r + c2.r);
  auto ps = tan_CP(c1, p), qs = tan_CP(c2, p);
  if (!ps.has_value() || !qs.has_value()) return {};
  // c1 counter-clock wise
  return ptt<line<FP>>{{ps.value().first, qs.value().first}, {ps.value().second, qs.value().second}};
}

}  // namespace tifa_libs::geo2d

#endif