#ifndef TIFALIBS_GEO2D_MIN_COVER_C
#define TIFALIBS_GEO2D_MIN_COVER_C

#include "make_c_ppp.hpp"
#include "rel_cp.hpp"

namespace tifa_libs::geo {

// min coverage circle of a set of points
//! accuracy maybe reduced without shuffling `vp` first
template <class FP>
circle<FP> min_cover_C(vec<point<FP>> const &vp) {
  circle ret{vp.front(), 0};
  u32 sz = (u32)vp.size();
  for (u32 i = 1; i < sz; ++i) {
    if (relation_CP(ret, vp[i]) != RELCP::outside_cp) continue;
    ret = circle{vp[i], 0};
    for (u32 j = 0; j < i; ++j) {
      if (relation_CP(ret, vp[j]) != RELCP::outside_cp) continue;
      ret = circle{mid_point(vp[i], vp[j]), dist_PP(vp[i], vp[j]) / 2};
      for (u32 k = 0; k < j; ++k) {
        if (relation_CP(ret, vp[k]) != RELCP::outside_cp) continue;
        ret = make_C_PPP(vp[i], vp[j], vp[k]);
      }
    }
  }
  return ret;
}

}  // namespace tifa_libs::geo

#endif