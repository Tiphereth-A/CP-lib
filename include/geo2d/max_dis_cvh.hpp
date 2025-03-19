#ifndef TIFALIBS_GEO2D_MAX_DIS_CVH
#define TIFALIBS_GEO2D_MAX_DIS_CVH

#include "cvh.hpp"

namespace tifa_libs::geo {

// Max distance between two convex hulls
template <class FP>
CEXP FP max_dis_CVH(cvh<FP> CR ch1, cvh<FP> CR ch2) NE {
  u32 is = 0, js = 0;
  const u32 n = ch1.size(), m = ch2.size();
  FP ans{};
  flt_ (u32, i, 0, n) is = ch1[i].y < ch1[is].y ? i : is;
  flt_ (u32, i, 0, m) js = ch2[i].y < ch2[js].y ? i : js;
  flt_ (u32, i, 0, n) {
    ans = max(ans, dist_PP(ch1[is], ch2[js]));
    int state;
    while ((state = sgn((ch1[is] - ch1[ch1.next(is)]) ^ (ch2[js] - ch2[ch2.next(js)]))) < 0) ans = max(ans, dist_PP(ch1[is], ch2[js = ch2.next(js)]));
    ans = max(ans, dist_PP(ch2[js], ch1[ch1.next(is = ch1.next(is))]));
    if (!state) ans = max(ans, dist_PP(ch1[is], ch2[js])), js = ch2.next(js);
  }
  return ans;
}

}  // namespace tifa_libs::geo

#endif