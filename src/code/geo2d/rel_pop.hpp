#ifndef TIFA_LIBS_GEO2D_REL_POP
#define TIFA_LIBS_GEO2D_REL_POP

#include "cvh.hpp"
#include "is_on_s.hpp"

namespace tifa_libs::geo {

// relation between polygon/convex hull and point
enum RELPoP {
  outside_pop,
  onborder_pop,
  onendpoint_pop,
  inside_pop
};

template <class FP>
RELPoP relation_PoP(polygon<FP> const &po, point<FP> const &p) {
  for (auto &&now : po.vs)
    if (now == p) return onendpoint_pop;
  bool result = false;
  for (usz i = 0; i < po.vs.size(); ++i) {
    point now_p = po.vs[i], next_p = po.vs[po.next(i)];
    if (is_on_S({now_p, next_p}, p)) return onborder_pop;
    if (!is_gt(now_p.y, next_p.y)) std::swap(now_p, next_p);
    if (is_gt(p.y, now_p.y) || !is_gt(p.y, next_p.y)) continue;
    result ^= sgn_cross(p, now_p, next_p) > 0;
  }
  return result ? inside_pop : outside_pop;
}

template <class FP>
RELPoP relation_CvhP(cvh<FP> const &cvh, point<FP> const &p) {
  for (auto &&now : cvh.vs)
    if (now == p) return onendpoint_pop;
  usz sz = cvh.vs.size();
  for (usz i = 0; i < sz; ++i)
    if (is_on_S({cvh.vs[i], cvh.vs[cvh.next(i)]}, p)) return onborder_pop;
  if (sz < 3) return outside_pop;
  if (is_pos(cross(cvh.vs.front(), p, cvh.vs[1])) || is_pos(cross(cvh.vs.front(), cvh.vs.back(), p))) return outside_pop;
  auto it = std::lower_bound(cvh.vs.begin() + 1, cvh.vs.end(), p, [&](point<FP> const &lhs, point<FP> const &rhs) { return is_pos(cross(cvh.vs.front(), lhs, rhs)); }) - 1;
  auto next_it = cvh.next(it);
  auto res = sgn_cross(p, *it, *next_it);
  if (res) return ~res ? inside_pop : outside_pop;
  return !res && !is_pos(dot(p, *it, *next_it)) ? inside_pop : outside_pop;
}

}  // namespace tifa_libs::geo

#endif