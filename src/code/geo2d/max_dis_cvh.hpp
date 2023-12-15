#ifndef TIFALIBS_GEO2D_MAX_DIS_CVH
#define TIFALIBS_GEO2D_MAX_DIS_CVH

#include "cvh.hpp"

namespace tifa_libs::geo {

// Max distance between two convex hulls
template <class FP>
constexpr FP max_dis_CVH(cvh<FP> const &ch1, cvh<FP> const &ch2) {
  u32 is = 0, js = 0;
  u32 szl = (u32)ch1.vs.size(), szr = (u32)ch2.vs.size();
  FP ans{};
  for (u32 i = 0; i < szl; ++i) is = ch1[i].y < ch1[is].y ? i : is;
  for (u32 i = 0; i < szr; ++i) js = ch2[i].y < ch2[js].y ? i : js;
  for (u32 i = 0; i < szl; ++i) {
    ans = std::max(ans, dist_PP(ch1[is], ch2[js]));
    int state;
    while ((state = sgn((ch1[is] - ch1[ch1.next(is)]) ^ (ch2[js] - ch2[ch2.next(js)]))) < 0) ans = std::max(ans, dist_PP(ch1[is], ch2[js = ch2.next(js)]));
    ans = std::max(ans, dist_PP(ch2[js], ch1[ch1.next(is = ch1.next(is))]));
    if (!state) {
      ans = std::max(ans, dist_PP(ch1[is], ch2[js]));
      js = ch2.next(js);
    }
  }
  return ans;
}

}  // namespace tifa_libs::geo

#endif