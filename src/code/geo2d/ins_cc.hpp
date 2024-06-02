#ifndef TIFALIBS_GEO2D_INS_CC
#define TIFALIBS_GEO2D_INS_CC

#include "rel_cc.hpp"

namespace tifa_libs::geo {

// intersection point of two circles
//! need to check whether two circles are the same
// maybe duplicate
template <class FP>
CEXP std::optional<ptt<point<FP>>> ins_CC(circle<FP> CR c1, circle<FP> CR c2) {
  assert(!is_eq(c1.o.x, c2.o.x) || !is_eq(c1.o.y, c2.o.y) || !is_eq(c1.r, c2.r));
  if (auto state = relation_CC(c1, c2); state == lyingin_cc || state == lyingout_cc) return {};
  const FP d = min(dist_PP(c1.o, c2.o), c1.r + c2.r), y = (c1.r * c1.r - c2.r * c2.r + d * d) / (2 * d), x = std::sqrt(c1.r * c1.r - y * y);
  const point dr = (c2.o - c1.o).do_unit(), q1 = c1.o + dr * y, q2 = rot90(dr) * x;
  return ptt<point<FP>>{q1 - q2, q1 + q2};
}

}  // namespace tifa_libs::geo

#endif