#ifndef TIFALIBS_GEO2D_MAXV_CVH_CNT
#define TIFALIBS_GEO2D_MAXV_CVH_CNT

#include "line.hpp"

namespace tifa_libs::geo {

// max number of vertices in vp which forms a convex hull
template <class FP>
CEXP u32 maxv_cvh_cnt(vec<point<FP>> CR vp) NE {
  const u32 n = (u32)vp.size();

  struct TIFA {
    line<FP> ln;
    u32 l, r;
    CEXP TIFA(u32 l, u32 r, point<FP> CR pl, point<FP> CR pr) NE : ln(pl, pr), l(l), r(r) {}
    CEXP auto operator<=>(TIFA CR r) CNE { return ln <=> r.ln; }
    CEXP bool operator==(TIFA CR r) CNE = default;
  };
  vec<TIFA> vl;
  flt_ (u32, i, 0, n)
    flt_ (u32, j, 0, n)
      if (i != j) vl.emplace_back(i, j, vp[i], vp[j]);
  sort(vl);
  veci f(n + 1);
  u32 ans = 0;
  flt_ (u32, i, 0, n) {
    fill(f, INT32_MIN), f[i] = 0;
    flt_ (u32, j, 0, (u32)vl.size()) f[vl[j].r] = max(f[vl[j].r], f[vl[j].l] + 1);
    ans = (u32)max((i32)ans, f[i]);
  }
  return ans;
}

}  // namespace tifa_libs::geo

#endif