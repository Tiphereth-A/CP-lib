#ifndef TIFALIBS_GEO2D_MIN_COVER_C
#define TIFALIBS_GEO2D_MIN_COVER_C

#include "make_c_ppp.hpp"
#include "rel_cp.hpp"

namespace tifa_libs::geo {

// min coverage circle of a set of points
//! shuffle `vp` first to avoid hack & improve accuracy
template <class FP>
CEXP circle<FP> min_cover_C(vec<point<FP>> CR vp) NE {
  circle<FP> ret{vp.front(), 0};
  const u32 n = (u32)vp.size();
  flt_ (u32, i, 1, n) {
    if (relation_CP(ret, vp[i]) != outside_cp) continue;
    ret = circle<FP>{vp[i], 0};
    flt_ (u32, j, 0, i) {
      if (relation_CP(ret, vp[j]) != outside_cp) continue;
      ret = circle<FP>{mid_point(vp[i], vp[j]), dist_PP(vp[i], vp[j]) / 2};
      flt_ (u32, k, 0, j)
        if (relation_CP(ret, vp[k]) == outside_cp) ret = make_C_PPP(vp[i], vp[j], vp[k]);
    }
  }
  return ret;
}

}  // namespace tifa_libs::geo

#endif