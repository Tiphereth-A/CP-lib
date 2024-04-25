#ifndef TIFALIBS_GEO2D_MAX_AREA_T
#define TIFALIBS_GEO2D_MAX_AREA_T

#include "cvh.hpp"
#include "triangle.hpp"

namespace tifa_libs::geo {

// Triangle inside with max area
template <class FP>
CEXP triangle<FP> max_area_T(cT_(cvh<FP>) ch) {
  if (ch.vs.size() < 3) return triangle<FP>{ch.vs[0], ch.vs[0], ch.vs[0]};
  u32 j = 1, k = 2;
  FP ans = 0, tmp, new_tmp;
  u32 is = 0, js = 1, ks = 2;
  for (u32 i = 0; i < ch.vs.size(); ++i) {
    if (i == j) j = ch.next(j);
    if (j == k) k = ch.next(k);
    if (is_gt(tmp = cross(ch.vs[i], ch.vs[j], ch.vs[k]), ans)) ans = tmp, is = i, js = j, ks = k;
    bool f = true;
    while (f) {
      f = false;
      if (is_gt(new_tmp = cross(ch.vs[i], ch.vs[j], ch.vs[ch.next(k)]), tmp)) {
        k = ch.next(k);
        if (is_gt(tmp = new_tmp, ans)) ans = tmp, is = i, js = j, ks = k;
        f = true;
      }
      if (is_gt(new_tmp = cross(ch.vs[i], ch.vs[ch.next(j)], ch.vs[k]), tmp)) {
        j = ch.next(j);
        if (is_gt(tmp = new_tmp, ans)) ans = tmp, is = i, js = j, ks = k;
        f = true;
      }
    }
  }
  return triangle{ch.vs[is], ch.vs[js], ch.vs[ks]};
}

}  // namespace tifa_libs::geo

#endif