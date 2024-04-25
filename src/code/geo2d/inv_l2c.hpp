#ifndef TIFALIBS_GEO2D_INV_L2C
#define TIFALIBS_GEO2D_INV_L2C

#include "inv_p2p.hpp"
#include "make_c_ppp.hpp"

namespace tifa_libs::geo {

// geometry inverse of a line
template <class FP>
CEXP circle<FP> inv_L2C(circle<FP> CR c, line<FP> CR l) {
  point p1 = inv_P2P(c, l.l), p2 = inv_P2P(c, l.r);
  return make_C_PPP(p1, p2, c.o);
}

}  // namespace tifa_libs::geo

#endif