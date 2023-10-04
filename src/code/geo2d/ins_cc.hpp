#ifndef TIFA_LIBS_GEO2D_INS_CC
#define TIFA_LIBS_GEO2D_INS_CC

#include "rel_cc.hpp"

namespace tifa_libs::geo2d {

// intersection point of two circles
//! need to check whether two circles are the same
// maybe duplicate
template <class FP>
std::optional<ptt<point<FP>>> ins_CC(circle<FP> const &c1, circle<FP> const &c2) {
  assert(!is_eq(c1.o.x, c2.o.x) || !is_eq(c1.o.y, c2.o.y) || !is_eq(c1.r, c2.r));
  auto state = relation_CC(c1, c2);
  if (state == RELCC::lyingin_cc || state == RELCC::lyingout_cc) return {};
  FP d = std::min(dist_PP(c1.o, c2.o), c1.r + c2.r);
  FP y = (c1.r * c1.r - c2.r * c2.r + d * d) / (2 * d), x = std::sqrt(c1.r * c1.r - y * y);
  point dr = (c2.o - c1.o).do_unit();
  point q1 = c1.o + dr * y, q2 = dr.do_rot90() * x;
  return {q1 - q2, q1 + q2};
}

}  // namespace tifa_libs::geo2d

#endif