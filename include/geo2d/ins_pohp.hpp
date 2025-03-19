#ifndef TIFALIBS_GEO2D_INS_POHP
#define TIFALIBS_GEO2D_INS_POHP

#include "cvh.hpp"

namespace tifa_libs::geo {

template <class FP>
CEXP cvh<FP> ins_PohP(cT_(cvh<FP>) poly, line<FP> CR l) NE {
  u32 n = poly.size();
  vec<point<FP>> vs;
  flt_ (u32, i, 0, n) {
    const point p1 = poly.vs[i], p2 = poly.vs[poly.next(i)];
    const int d1 = l.toleft(p1), d2 = l.toleft(p2);
    if (d1 >= 0) vs.push_back(p1);
    if (d1 * d2 < 0) vs.push_back(ins_LL({p1, p2}, l));
  }
  return cvh<FP>(vs, true);
}

}  // namespace tifa_libs::geo

#endif