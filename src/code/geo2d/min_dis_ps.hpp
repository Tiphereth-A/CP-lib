#ifndef TIFALIBS_GEO2D_MIN_DIS_PS
#define TIFALIBS_GEO2D_MIN_DIS_PS

#include "dist_pp.hpp"

namespace tifa_libs::geo {

// min distance of a set of DISTINCT points in range [l, r)
//! need to sort `vp` first by the ascending order of x
template <class FP, bool get_index = false>
CEXP auto min_dis_Ps(vec<point<FP>> CR vp, u32 l, u32 r) {
  std::conditional_t<get_index, std::tuple<FP, u32, u32>, FP> ret;
  if CEXP (get_index) ret = {std::numeric_limits<FP>::max(), 0, 0};
  else ret = std::numeric_limits<FP>::max();
  if (r - l <= 5) {
    flt_ (u32, i, l, r)
      flt_ (u32, j, l, i)
        if CEXP (get_index) ret = min(ret, std::make_tuple(dist_PP(vp[i], vp[j]), i, j));
        else ret = min(ret, dist_PP(vp[i], vp[j]));
    return ret;
  }
  const u32 mid = r - (r - l) / 2;
  ret = min(min_dis_Ps<FP, get_index>(vp, l, mid), min_dis_Ps<FP, get_index>(vp, mid, r));
  vec<point<FP>> q;
  vecu idx;
  flt_ (u32, i, l, r)
    if CEXP (get_index) {
      if (abs(vp[i].x - vp[mid].x) <= std::get<0>(ret)) q.push_back(vp[i]), idx.push_back(i);
    } else if (abs(vp[i].x - vp[mid].x) <= ret) q.push_back(vp[i]);
  if CEXP (get_index) std::ranges::stable_sort(idx, [&](u32 l, u32 r) -> bool { return vp[l].y < vp[r].y; });
  std::ranges::stable_sort(q, [](point<FP> CR l, point<FP> CR r) -> bool { return l.y < r.y; });
  flt_ (u32, i, 1, (u32)q.size())
    if CEXP (get_index)
      for (u32 j = i - 1; ~j && q[j].y >= q[i].y - std::get<0>(ret); --j) ret = min(ret, std::make_tuple(dist_PP(q[i], q[j]), idx[i], idx[j]));
    else
      for (u32 j = i - 1; ~j && q[j].y >= q[i].y - ret; --j) ret = min(ret, dist_PP(q[i], q[j]));
  return ret;
}

}  // namespace tifa_libs::geo

#endif