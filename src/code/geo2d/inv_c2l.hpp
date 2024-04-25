#ifndef TIFALIBS_GEO2D_INV_C2L
#define TIFALIBS_GEO2D_INV_C2L

#include "inv_p2p.hpp"
#include "line.hpp"

namespace tifa_libs::geo {

// geometry inverse of a circle which pass through the inversion center
template <class FP>
CEXP line<FP> inv_C2L(circle<FP> CR c, circle<FP> CR c1) {
  point v = (c1.o - c.o).do_rot90();
  return {inv_P2P(c, c1.o + v), inv_P2P(c, c1.o - v)};
}

}  // namespace tifa_libs::geo

#endif