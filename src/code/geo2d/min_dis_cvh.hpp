#ifndef TIFA_LIBS_GEO2D_MIN_DIS_CVH
#define TIFA_LIBS_GEO2D_MIN_DIS_CVH

#include "cvh.hpp"

namespace tifa_libs::geo2d {

// Min distance between two convex hulls
template <class FP>
FP min_dis_CVH(cvh<FP> const &cvhl, cvh<FP> const &cvhr) {
  size_t is = 0, js = 0;
  size_t szl = cvhl.vs.size(), szr = cvhr.vs.size();
  FP ans = std::numeric_limits<FP>::max();
  for (size_t i = 0; i < szl; ++i) is = cvhl[i].y < cvhl[is].y ? i : is;
  for (size_t i = 0; i < szr; ++i) js = cvhr[i].y < cvhr[js].y ? i : js;
  for (size_t i = 0; i < szl; ++i) {
    int state;
    while ((state = sgn((cvhl[is] - cvhl[cvhl.next(is)]) ^ (cvhr[js] - cvhr[cvhr.next(js)]))) < 0) js = cvhr.next(js);
    ans = std::min(ans, state ? dist_PS(cvhr[js], {cvhl[is], cvhl[cvhl.next(is)]}) : dist_SS({cvhl[is], cvhl[cvhl.next(is)]}, {cvhr[js], cvhr[cvhr.next(js)]}));
    is = cvhl.next(is);
  }
  return ans;
}

}  // namespace tifa_libs::geo2d

#endif