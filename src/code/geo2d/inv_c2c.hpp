#ifndef TIFALIBS_GEO2D_INV_C2C
#define TIFALIBS_GEO2D_INV_C2C

#include "inv_p2p.hpp"

namespace tifa_libs::geo {

// geometry inverse of a circle which DOES NOT pass through the inversion center
template <class FP>
CEXP circle<FP> inv_C2C(circle<FP> CR c, circle<FP> CR c1) {
  point v = (c1.o - c.o).do_unit();
  point p1 = inv_P2P(c, c1.o + v * c1.r), p2 = inv_P2P(c, c1.o - v * c1.r);
  return {mid_point(p1, p2), dist_PP(p1, p2) / 2};
}

}  // namespace tifa_libs::geo

#endif