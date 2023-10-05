#ifndef TIFA_LIBS_GEO2D_INV_C2C
#define TIFA_LIBS_GEO2D_INV_C2C

#include "inv_p2p.hpp"

namespace tifa_libs::geo {

// geometry inverse of a circle which DOES NOT pass through the inversion center
template <class FP>
constexpr circle<FP> inv_C2C(circle<FP> const &c, circle<FP> const &c1) {
  point v = (c1.o - c.o).do_unit();
  point p1 = inv_P2P(c, c1.o + v * c1.r), p2 = inv_P2P(c, c1.o - v * c1.r);
  return {mid_point(p1, p2), dist_PP(p1, p2) / 2};
}

}  // namespace tifa_libs::geo

#endif