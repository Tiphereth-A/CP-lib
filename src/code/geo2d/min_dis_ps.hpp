#ifndef TIFA_LIBS_GEO2D_MIN_DIS_PS
#define TIFA_LIBS_GEO2D_MIN_DIS_PS

#include "dist_pp.hpp"

namespace tifa_libs::geo {

// min distance of a set of points in range [l, r)
//! need to sort `vp` first by the ascending order of x
template <class FP>
FP min_dis_Ps(vec<point<FP>> const &vp, u32 l, u32 r) {
  FP ret = std::numeric_limits<FP>::max();
  if (r - l <= 5) {
    for (u32 i = l; i < r; ++i)
      for (u32 j = l; j < i; ++j) ret = std::min(ret, dist_PP(vp[i], vp[j]));
    return ret;
  }
  u32 mid = r - (r - l) / 2;
  ret = std::min(min_dis_Ps(vp, l, mid), min_dis_Ps(vp, mid, r));
  vec<point<FP>> q;
  for (u32 i = l; i < r; ++i)
    if (std::abs(vp[i].x - vp[mid].x) <= ret) q.push_back(vp[i]);
  std::stable_sort(q.begin(), q.end(), [](auto const &l, auto const &r) -> bool { return l.y < r.y; });
  for (u32 i = 1; i < q.size(); ++i)
    for (u32 j = i - 1; ~j && q[j].y >= q[i].y - ret; --j) ret = std::min(ret, dist_PP(q[i], q[j]));
  return ret;
}

}  // namespace tifa_libs::geo

#endif