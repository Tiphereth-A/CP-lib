#ifndef TIFALIBS_GEO2D_REL_POP
#define TIFALIBS_GEO2D_REL_POP

#include "cvh.hpp"
#include "dot.hpp"
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
CEXP RELPoP relation_PoP(polygon<FP> CR po, point<FP> CR p) {
  for (auto &&now : po.vs)
    if (now == p) return onendpoint_pop;
  bool result = false;
  for (u32 i = 0; i < po.vs.size(); ++i) {
    point now_p = po.vs[i], next_p = po.vs[po.next(i)];
    if (is_on_S({now_p, next_p}, p)) return onborder_pop;
    if (!is_gt(now_p.y, next_p.y)) swap(now_p, next_p);
    if (is_gt(p.y, now_p.y) || !is_gt(p.y, next_p.y)) continue;
    result ^= sgn_cross(p, now_p, next_p) > 0;
  }
  return result ? inside_pop : outside_pop;
}

template <class FP>
CEXP RELPoP relation_CvhP(cT_(cvh<FP>) cvh, point<FP> CR p) {
  for (auto &&now : cvh.vs)
    if (now == p) return onendpoint_pop;
  u32 sz = (u32)cvh.vs.size();
  flt_ (u32, i, 0, sz)
    if (is_on_S({cvh.vs[i], cvh.vs[cvh.next(i)]}, p)) return onborder_pop;
  if (sz < 3) return outside_pop;
  if (is_pos(cross(cvh.vs.front(), p, cvh.vs[1])) || is_pos(cross(cvh.vs.front(), cvh.vs.back(), p))) return outside_pop;
  auto it = std::lower_bound(cvh.vs.begin() + 1, cvh.vs.end(), p, [&](point<FP> CR l, point<FP> CR r) { return is_pos(cross(cvh.vs.front(), l, r)); }) - 1;
  auto next_it = cvh.next(it);
  auto res = sgn_cross(p, *it, *next_it);
  if (res) return ~res ? inside_pop : outside_pop;
  return !res && !is_pos(dot(p, *it, *next_it)) ? inside_pop : outside_pop;
}

}  // namespace tifa_libs::geo

#endif