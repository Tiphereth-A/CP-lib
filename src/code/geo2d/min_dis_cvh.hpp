#ifndef TIFA_LIBS_GEO2D_MIN_DIS_CVH
#define TIFA_LIBS_GEO2D_MIN_DIS_CVH

#include "cvh.hpp"

namespace tifa_libs::geo {

// Min distance between two convex hulls
template <class FP>
FP min_dis_CVH(cvh<FP> const &ch1, cvh<FP> const &ch2) {
  usz is = 0, js = 0;
  usz szl = ch1.vs.size(), szr = ch2.vs.size();
  FP ans = std::numeric_limits<FP>::max();
  for (usz i = 0; i < szl; ++i) is = ch1[i].y < ch1[is].y ? i : is;
  for (usz i = 0; i < szr; ++i) js = ch2[i].y < ch2[js].y ? i : js;
  for (usz i = 0; i < szl; ++i) {
    int state;
    while ((state = sgn((ch1[is] - ch1[ch1.next(is)]) ^ (ch2[js] - ch2[ch2.next(js)]))) < 0) js = ch2.next(js);
    ans = std::min(ans, state ? dist_PS(ch2[js], {ch1[is], ch1[ch1.next(is)]}) : dist_SS({ch1[is], ch1[ch1.next(is)]}, {ch2[js], ch2[ch2.next(js)]}));
    is = ch1.next(is);
  }
  return ans;
}

}  // namespace tifa_libs::geo

#endif