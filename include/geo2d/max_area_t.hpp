#ifndef TIFALIBS_GEO2D_MAX_AREA_T
#define TIFALIBS_GEO2D_MAX_AREA_T

#include "cvh.hpp"
#include "triangle.hpp"

namespace tifa_libs::geo {

// Triangle inside with max area
template <class FP>
CEXP triangle<FP> max_area_T(cT_(cvh<FP>) ch) NE {
  if (ch.size() < 3) return triangle<FP>{ch.vs[0], ch.vs[0], ch.vs[0]};
  u32 j = 1, k = 2;
  FP ans = 0, _, _2;
  u32 is = 0, js = 1, ks = 2;
  flt_ (u32, i, 0, ch.size()) {
    if (i == j) j = ch.next(j);
    if (j == k) k = ch.next(k);
    if (is_gt(_ = cross(ch.vs[i], ch.vs[j], ch.vs[k]), ans)) ans = _, is = i, js = j, ks = k;
    bool f = true;
    while (f) {
      f = false;
      if (is_gt(_2 = cross(ch.vs[i], ch.vs[j], ch.vs[ch.next(k)]), _)) {
        if (k = ch.next(k); is_gt(_ = _2, ans)) ans = _, is = i, js = j, ks = k;
        f = true;
      }
      if (is_gt(_2 = cross(ch.vs[i], ch.vs[ch.next(j)], ch.vs[k]), _)) {
        if (j = ch.next(j); is_gt(_ = _2, ans)) ans = _, is = i, js = j, ks = k;
        f = true;
      }
    }
  }
  return triangle{ch.vs[is], ch.vs[js], ch.vs[ks]};
}

}  // namespace tifa_libs::geo

#endif