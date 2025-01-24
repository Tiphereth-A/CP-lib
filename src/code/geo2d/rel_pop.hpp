#ifndef TIFALIBS_GEO2D_REL_POP
#define TIFALIBS_GEO2D_REL_POP

#include "is_on_s.hpp"
#include "polygon.hpp"

namespace tifa_libs::geo {

// relation between polygon and point
enum RELPoP { outside_pop,
              onborder_pop,
              onendpoint_pop,
              inside_pop };

template <class FP>
CEXP RELPoP relation_PoP(polygon<FP> CR po, point<FP> CR p) NE {
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

}  // namespace tifa_libs::geo

#endif