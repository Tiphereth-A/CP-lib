#ifndef TIFALIBS_GEO2D_INV_C2C
#define TIFALIBS_GEO2D_INV_C2C

#include "inv_p2p.hpp"

namespace tifa_libs::geo {

// geometry inverse of a circle which DOES NOT pass through the inversion center
// @param cc reference circle
template <class FP>
CEXP circle<FP> inv_C2C(circle<FP> CR rc, circle<FP> CR c) {
  const point v = (c.o - rc.o).do_unit();
  const point p1 = inv_P2P(rc, c.o + v * c.r), p2 = inv_P2P(rc, c.o - v * c.r);
  return {mid_point(p1, p2), dist_PP(p1, p2) / 2};
}
// cc.r == 1
// @param cc reference circle
template <class FP>
CEXP circle<FP> inv_C2C(point<FP> CR ro, circle<FP> CR c) {
  const point v = (c.o - ro).do_unit();
  const point p1 = inv_P2P(ro, c.o + v * c.r), p2 = inv_P2P(ro, c.o - v * c.r);
  return {mid_point(p1, p2), dist_PP(p1, p2) / 2};
}

}  // namespace tifa_libs::geo

#endif