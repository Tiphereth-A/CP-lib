#ifndef TIFALIBS_GEO2D_MAX_COVER_PS
#define TIFALIBS_GEO2D_MAX_COVER_PS

#include "ang2pi_pp.hpp"
#include "dist_pp.hpp"

namespace tifa_libs::geo {

// max number of points covered by a circle with radius @r
template <class FP>
CEXP u64 max_cover_Ps(vec<point<FP>> CR vp, FP r) {
  if (is_neg(r)) return 0;
  if (is_zero(r)) return 1;
  const FP diam = r * 2;
  u64 ans = 1;
  vecp<FP, i64> angles;
  FP dist;
  flt_ (u32, i, 0, (u32)vp.size()) {
    angles.clear();
    flt_ (u32, j, 0, (u32)vp.size()) {
      if (i == j || is_gt(dist = dist_PP(vp[i], vp[j]), diam)) continue;
      FP delta = std::acos(dist / diam), polar = ang2pi_PP(vp[i], vp[j]);
      angles.emplace_back(polar - delta, 1);
      angles.emplace_back(polar + delta, -1);
    }
    std::ranges::sort(angles);
    u64 sum = 0;
    flt_ (u32, j, 0, (u32)angles.size()) ans = max(ans, sum += angles[j].second);
  }
  return ans;
}

}  // namespace tifa_libs::geo

#endif