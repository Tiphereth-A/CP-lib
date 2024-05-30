#ifndef TIFALIBS_GEO2D_INV_P2P
#define TIFALIBS_GEO2D_INV_P2P

#include "circle.hpp"

namespace tifa_libs::geo {

// geometry inverse of a point
// @param rc reference circle
template <class FP>
CEXP point<FP> inv_P2P(circle<FP> CR rc, point<FP> CR p) {
  const point v = p - rc.o;
  return rc.o + v * (rc.r * rc.r / v.norm2());
}
// rc.r == 1
// @param rc reference circle
template <class FP>
CEXP point<FP> inv_P2P(point<FP> CR ro, point<FP> CR p) {
  const point v = p - ro;
  return ro + v / v.norm2();
}

}  // namespace tifa_libs::geo

#endif