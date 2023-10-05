#ifndef TIFA_LIBS_GEO2D_COVERAGE_RECT_WITH_MIN_AREA
#define TIFA_LIBS_GEO2D_COVERAGE_RECT_WITH_MIN_AREA

#include "cvh.hpp"

namespace tifa_libs::geo {

// Coverage rectangle with min area
template <class FP>
polygon<FP> coverage_rect_with_min_area(cvh<FP> const &lhs) {
  size_t sz = lhs.vs.size();
  if (sz == 0) return lhs;
  if (sz == 1) return polygon{vec<point<FP>>{lhs[0], lhs[0], lhs[0], lhs[0]}};
  if (sz == 2) return polygon{vec<point<FP>>{lhs[0], lhs[0], lhs[1], lhs[1]}};
  FP ans = std::numeric_limits<FP>::max();
  size_t r = 1, p = 1, q = 1;
  size_t ans_i, ans_r, ans_p, ans_q;
  for (size_t i = 0; i < sz; ++i) {
    while (!is_neg(cross(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[lhs.next(r)]) - cross(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[r]))) r = lhs.next(r);
    while (!is_neg(dot(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[lhs.next(p)]) - dot(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[p]))) p = lhs.next(p);
    if (i == 0) q = p;
    while (!is_pos(dot(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[lhs.next(q)]) - dot(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[q]))) q = lhs.next(q);
    FP tmp = cross(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[r]) * (dot(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[p]) - dot(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[q])) / (lhs.vs[i] - lhs.vs[lhs.next(i)]).norm2();
    if (ans > tmp) {
      ans = tmp;
      ans_i = i;
      ans_r = r;
      ans_p = p;
      ans_q = q;
    }
  }
  point dir = line{lhs[ans_i], lhs[lhs.next(ans_i)]}.direction(), vdir = rot90(dir);
  line li{lhs[ans_i], lhs[ans_i] + dir}, lp{lhs[ans_p], lhs[ans_p] + vdir}, lr{lhs[ans_r], lhs[ans_r] + dir}, lq{lhs[ans_q], lhs[ans_q] + vdir};
  polygon ret{vec<point<FP>>{ins_LL(li, lp), ins_LL(lp, lr), ins_LL(lr, lq), ins_LL(lq, li)}};
  return ret;
}

}  // namespace tifa_libs::geo

#endif