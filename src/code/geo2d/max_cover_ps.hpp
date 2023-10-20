#ifndef TIFA_LIBS_GEO2D_MAX_COVER_PS
#define TIFA_LIBS_GEO2D_MAX_COVER_PS

#include "ang2pi_pp.hpp"
#include "dist_pp.hpp"

namespace tifa_libs::geo {

// max number of points covered by a circle with radius @r
template <class FP>
u64 max_cover_Ps(vec<point<FP>> const &vp, FP r) {
  if (is_neg(r)) return 0;
  if (is_zero(r)) return 1;
  const FP diam = r * 2;
  u64 ans = 1;
  vec<std::pair<FP, i64>> angles;
  FP dist;
  for (usz i = 0; i < vp.size(); ++i) {
    angles.clear();
    for (usz j = 0; j < vp.size(); ++j) {
      if (i == j || is_gt(dist = dist_PP(vp[i], vp[j]), diam)) continue;
      FP delta = std::acos(dist / diam), polar = ang2pi_PP(vp[i], vp[j]);
      angles.emplace_back(polar - delta, 1);
      angles.emplace_back(polar + delta, -1);
    }
    std::sort(angles.begin(), angles.end());
    u64 sum = 0;
    for (usz j = 0; j < angles.size(); ++j) ans = std::max(ans, sum += angles[j].second);
  }
  return ans;
}

}  // namespace tifa_libs::geo

#endif