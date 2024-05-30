#ifndef TIFALIBS_GEO2D_INV_L2C
#define TIFALIBS_GEO2D_INV_L2C

#include "inv_p2p.hpp"
#include "make_c_ppp.hpp"

namespace tifa_libs::geo {

// geometry inverse of a line
// @param rc reference circle
template <class FP>
CEXP circle<FP> inv_L2C(circle<FP> CR rc, line<FP> CR l) {
  const point p1 = inv_P2P(rc, l.l), p2 = inv_P2P(rc, l.r);
  return make_C_PPP(p1, p2, rc.o);
}
// rc.r == 1
// @param rc reference circle
template <class FP>
CEXP circle<FP> inv_L2C(point<FP> CR o, line<FP> CR l) {
  const point p1 = inv_P2P(o, l.l), p2 = inv_P2P(o, l.r);
  return make_C_PPP(p1, p2, o);
}

}  // namespace tifa_libs::geo

#endif