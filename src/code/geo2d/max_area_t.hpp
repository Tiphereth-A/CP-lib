#ifndef TIFA_LIBS_GEO2D_MAX_AREA_T
#define TIFA_LIBS_GEO2D_MAX_AREA_T

#include "cvh.hpp"
#include "triangle.hpp"

namespace tifa_libs::geo {

// Triangle inside with max area
template <class FP>
triangle<FP> max_area_T(cvh<FP> const &cvh) {
  if (cvh.vs.size() < 3) return triangle<FP>{cvh.vs[0], cvh.vs[0], cvh.vs[0]};
  size_t j = 1, k = 2;
  FP ans = 0, tmp, new_tmp;
  size_t is = 0, js = 1, ks = 2;
  for (size_t i = 0; i < cvh.vs.size(); ++i) {
    if (i == j) j = cvh.next(j);
    if (j == k) k = cvh.next(k);
    if (is_ge(tmp = cross(cvh.vs[i], cvh.vs[j], cvh.vs[k]), ans)) {
      ans = tmp;
      is = i;
      js = j;
      ks = k;
    }
    bool f = true;
    while (f) {
      f = false;
      if (is_ge(new_tmp = cross(cvh.vs[i], cvh.vs[j], cvh.vs[cvh.next(k)]), tmp)) {
        k = cvh.next(k);
        if (is_ge(tmp = new_tmp, ans)) {
          ans = tmp;
          is = i;
          js = j;
          ks = k;
        }
        f = true;
      }
      if (is_ge(new_tmp = cross(cvh.vs[i], cvh.vs[cvh.next(j)], cvh.vs[k]), tmp)) {
        j = cvh.next(j);
        if (is_ge(tmp = new_tmp, ans)) {
          ans = tmp;
          is = i;
          js = j;
          ks = k;
        }
        f = true;
      }
    }
  }
  return triangle{cvh.vs[is], cvh.vs[js], cvh.vs[ks]};
}

}  // namespace tifa_libs::geo

#endif