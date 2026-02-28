#ifndef TIFALIBS_GEO2D_INV_C2L_LIB
#define TIFALIBS_GEO2D_INV_C2L_LIB

#include "../../ds/l/lib.hpp"
#include "../p2p/lib.hpp"

namespace tifa_libs::geo {

// geometry inverse of a circle which pass through the inversion center
// @param rc reference circle
// @param o circle center
template <class FP>
CEXP line<FP> inv_C2L(circle<FP> CR rc, point<FP> CR o) NE {
  const point v = (o - rc.o).do_rot90();
  return {inv_P2P(rc, o + v), inv_P2P(rc, o - v)};
}
// rc.r == 1
// @param rc reference circle
// @param o circle center
template <class FP>
CEXP line<FP> inv_C2L(point<FP> CR ro, point<FP> CR o) NE {
  const point v = (o - ro).do_rot90();
  return {inv_P2P(ro, o + v), inv_P2P(ro, o - v)};
}

}  // namespace tifa_libs::geo

#endif