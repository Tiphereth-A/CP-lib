#ifndef TIFA_LIBS_GEO2D_MAX_DIS_CVH
#define TIFA_LIBS_GEO2D_MAX_DIS_CVH

#include "cvh.hpp"

namespace tifa_libs::geo2d {

// Max distance between two convex hulls
template <class FP>
FP max_dis_CVH(cvh<FP> const &cvhl, cvh<FP> const &cvhr) {
  size_t is = 0, js = 0;
  size_t szl = cvhl.vs.size(), szr = cvhr.vs.size();
  FP ans{};
  for (size_t i = 0; i < szl; ++i) is = cvhl[i].y < cvhl[is].y ? i : is;
  for (size_t i = 0; i < szr; ++i) js = cvhr[i].y < cvhr[js].y ? i : js;
  for (size_t i = 0; i < szl; ++i) {
    int state;
    ans = std::max(ans, dist_PP(cvhl[is], cvhr[js]));
    while ((state = sgn((cvhl[is] - cvhl[cvhl.next(is)]) ^ (cvhr[js] - cvhr[cvhr.next(js)]))) < 0) ans = std::max(ans, dist_PP(cvhl[is], cvhr[js = cvhr.next(js)]));
    ans = std::max(ans, dist_PP(cvhr[js], cvhl[cvhl.next(is = cvhl.next(is))]));
    if (!state) {
      ans = std::max(ans, dist_PP(cvhl[is], cvhr[js]));
      js = cvhr.next(js);
    }
  }
  return ans;
}

}  // namespace tifa_libs::geo2d

#endif