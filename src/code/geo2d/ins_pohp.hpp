#ifndef TIFALIBS_GEO2D_INS_POHP
#define TIFALIBS_GEO2D_INS_POHP

#include "cvh.hpp"

namespace tifa_libs::geo {

template <class FP>
CEXP cvh<FP> ins_PohP(cT_(cvh<FP>) poly, line<FP> CR l) {
  u32 n = (u32)poly.vs.size();
  vec<point<FP>> vs;
  flt_ (u32, i, 0, n) {
    point p1 = poly.vs[i], p2 = poly.vs[poly.next(i)];
    int d1 = sgn_cross(l.l, l.r, p1), d2 = sgn_cross(l.l, l.r, p2);
    if (d1 >= 0) vs.push_back(p1);
    if (d1 * d2 < 0) vs.push_back(ins_LL({p1, p2}, l));
  }
  return cvh<FP>(vs, true);
}

}  // namespace tifa_libs::geo

#endif