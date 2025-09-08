#ifndef TIFALIBS_GEO2D_MAX_COVER_PS
#define TIFALIBS_GEO2D_MAX_COVER_PS

#include "ang_pp.hpp"
#include "dist_pp.hpp"

namespace tifa_libs::geo {

// max number of points covered by a circle with radius @r
template <class FP>
CEXP u64 max_cover_Ps(vec<point<FP>> CR vp, FP r) NE {  //! BUG exists...
  retif_((is_neg(r)) [[unlikely]], 0);
  retif_((is_zero(r)) [[unlikely]], 1);
  const FP diam = r * 2;
  u64 ans = 1;
  vecp<FP, i64> angs;
  FP dist;
  flt_ (u32, i, 0, (u32)vp.size()) {
    angs.clear();
    flt_ (u32, j, 0, (u32)vp.size()) {
      if (i == j || is_gt(dist = dist_PP(vp[i], vp[j]), diam)) continue;
      FP delta = std::acos(dist / diam), polar = ang2pi_PP(vp[i], vp[j]);
      angs.emplace_back(polar - delta, 1), angs.emplace_back(polar + delta, -1);
    }
    sort(angs);
    i64 sum = 0;
    flt_ (u32, j, 0, (u32)angs.size()) ans = max(ans, (u64)max(0_i64, sum += angs[j].second));
  }
  return ans;
}

}  // namespace tifa_libs::geo

#endif