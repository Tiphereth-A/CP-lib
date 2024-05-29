#ifndef TIFALIBS_GEO2D_MAXV_CVH_CNT
#define TIFALIBS_GEO2D_MAXV_CVH_CNT

#include "line.hpp"

namespace tifa_libs::geo {
namespace maxv_cvh_cnt_impl_ {
template <class FP>
struct TIFA {
  u32 l, r;
  line<FP> ln;
  CEXP TIFA(u32 l, u32 r, point<FP> CR pl, point<FP> CR pr) : l(l), r(r), ln(pl, pr) {}
  friend CEXP auto operator<=>(TIFA CR l, TIFA CR r) { return l.ln <=> r.ln; }
};
}  // namespace maxv_cvh_cnt_impl_

// max number of vertices in vp which forms a convex hull
template <class FP>
CEXP u32 maxv_cvh_cnt(vec<point<FP>> CR vp) {
  u32 n = (u32)vp.size();
  vec<maxv_cvh_cnt_impl_::TIFA<FP>> vl;
  flt_ (u32, i, 0, n)
    flt_ (u32, j, 0, n) {
      if (i == j) continue;
      vl.emplace_back(i, j, vp[i], vp[j]);
    }
  std::sort(vl.begin(), vl.end());
  vec<i32> f(n + 1);
  u32 ans = 0;
  flt_ (u32, i, 0, n) {
    std::ranges::fill(f, INT32_MIN);
    f[i] = 0;
    flt_ (u32, j, 0, (u32)vl.size()) f[vl[j].r] = max(f[vl[j].r], f[vl[j].l] + 1);
    ans = (u32)max((i32)ans, f[i]);
  }
  return ans;
}

}  // namespace tifa_libs::geo

#endif