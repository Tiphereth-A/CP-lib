#ifndef TIFALIBS_GEO2D_MIN_DIS_CVH
#define TIFALIBS_GEO2D_MIN_DIS_CVH

#include "cvh.hpp"

namespace tifa_libs::geo {

// Min distance between two convex hulls
template <class FP>
CEXP FP min_dis_CVH(cT_(cvh<FP>) ch1, cT_(cvh<FP>) ch2) {
  u32 is = 0, js = 0;
  u32 szl = ch1.size(), szr = ch2.size();
  FP ans = std::numeric_limits<FP>::max();
  flt_ (u32, i, 0, szl) is = ch1[i].y < ch1[is].y ? i : is;
  flt_ (u32, i, 0, szr) js = ch2[i].y < ch2[js].y ? i : js;
  flt_ (u32, i, 0, szl) {
    int state;
    while ((state = sgn((ch1[is] - ch1[ch1.next(is)]) ^ (ch2[js] - ch2[ch2.next(js)]))) < 0) js = ch2.next(js);
    ans = min(ans, state ? dist_PS(ch2[js], {ch1[is], ch1[ch1.next(is)]}) : dist_SS({ch1[is], ch1[ch1.next(is)]}, {ch2[js], ch2[ch2.next(js)]}));
    is = ch1.next(is);
  }
  return ans;
}

}  // namespace tifa_libs::geo

#endif