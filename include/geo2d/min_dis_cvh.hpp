#ifndef TIFALIBS_GEO2D_MIN_DIS_CVH
#define TIFALIBS_GEO2D_MIN_DIS_CVH

#include "cvh.hpp"

namespace tifa_libs::geo {

// Min distance between two convex hulls
template <class FP>
CEXP FP min_dis_CVH(cvh<FP> CR ch1, cvh<FP> CR ch2) NE {
  u32 is = 0, js = 0;
  const u32 n = ch1.size(), m = ch2.size();
  FP ans = std::numeric_limits<FP>::max();
  flt_ (u32, i, 0, n) is = ch1[i].y < ch1[is].y ? i : is;
  flt_ (u32, i, 0, m) js = ch2[i].y < ch2[js].y ? i : js;
  flt_ (u32, i, 0, n) {
    int state;
    while ((state = sgn((ch1[is] - ch1[ch1.next(is)]) ^ (ch2[js] - ch2[ch2.next(js)]))) < 0) js = ch2.next(js);
    ans = min(ans, state ? dist_PS(ch2[js], {ch1[is], ch1[ch1.next(is)]})
                         : dist_SS({ch1[is], ch1[ch1.next(is)]}, {ch2[js], ch2[ch2.next(js)]}));
    is = ch1.next(is);
  }
  return ans;
}

}  // namespace tifa_libs::geo

#endif