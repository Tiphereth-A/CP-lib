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
  flt_ (u32, i, 0, po.size()) {
    point u = po.vs[i], v = po.vs[po.next(i)];
    if (is_on_S({u, v}, p)) return onborder_pop;
    if (!is_gt(u.y, v.y)) swap(u, v);
    if (is_gt(p.y, u.y) || !is_gt(p.y, v.y)) continue;
    result ^= sgn_cross(p, u, v) > 0;
  }
  return result ? inside_pop : outside_pop;
}

template <class FP>
CEXP RELPoP relation_CvhP(cT_(cvh<FP>) cvh, point<FP> CR p) {
  for (auto &&now : cvh.vs)
    if (now == p) return onendpoint_pop;
  const u32 n = cvh.size();
  flt_ (u32, i, 0, n)
    if (is_on_S({cvh.vs[i], cvh.vs[cvh.next(i)]}, p)) return onborder_pop;
  if (n < 3) return outside_pop;
  if (is_pos(cross(cvh.vs[0], p, cvh.vs[1])) || is_pos(cross(cvh.vs[0], cvh.vs.back(), p))) return outside_pop;
  auto it = std::lower_bound(cvh.vs.begin() + 1, cvh.vs.end(), p, [&](point<FP> CR l, point<FP> CR r) { return is_pos(cross(cvh.vs[0], l, r)); }) - 1;
  auto next_it = cvh.next(it);
  if (auto res = sgn_cross(p, *it, *next_it); res) return ~res ? inside_pop : outside_pop;
  else return !res && !is_pos(dot(p, *it, *next_it)) ? inside_pop : outside_pop;
}

}  // namespace tifa_libs::geo

#endif