#ifndef TIFALIBS_GEO2D_MIN_DIS_PS
#define TIFALIBS_GEO2D_MIN_DIS_PS

#include "dist_pp.hpp"

namespace tifa_libs::geo {

// min distance of a set of points in range [l, r)
//! need to sort `vp` first by the ascending order of x
template <class FP>
CEXP FP min_dis_Ps(vec<point<FP>> CR vp, u32 l, u32 r) {
  FP ret = std::numeric_limits<FP>::max();
  if (r - l <= 5) {
    flt_ (u32, i, l, r)
      flt_ (u32, j, l, i) ret = min(ret, dist_PP(vp[i], vp[j]));
    return ret;
  }
  u32 mid = r - (r - l) / 2;
  ret = min(min_dis_Ps(vp, l, mid), min_dis_Ps(vp, mid, r));
  vec<point<FP>> q;
  flt_ (u32, i, l, r)
    if (abs(vp[i].x - vp[mid].x) <= ret) q.push_back(vp[i]);
  std::ranges::stable_sort(q, [](point<FP> CR l, point<FP> CR r) -> bool { return l.y < r.y; });
  for (u32 i = 1; i < q.size(); ++i)
    for (u32 j = i - 1; ~j && q[j].y >= q[i].y - ret; --j) ret = min(ret, dist_PP(q[i], q[j]));
  return ret;
}

}  // namespace tifa_libs::geo

#endif