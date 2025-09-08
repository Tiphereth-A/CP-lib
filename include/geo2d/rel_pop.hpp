#ifndef TIFALIBS_GEO2D_REL_POP
#define TIFALIBS_GEO2D_REL_POP

#include "is_on_s.hpp"
#include "polygon.hpp"

namespace tifa_libs::geo {

// relation between polygon and point
// clang-format off
enum class RELPoP : u8 { outside, onborder, onendpoint, inside };
// clang-format on

template <class FP>
CEXP RELPoP relation_PoP(polygon<FP> CR po, point<FP> CR p) NE {
  for (auto &&now : po.vs)
    if (now == p) return RELPoP::onendpoint;
  bool result = false;
  flt_ (u32, i, 0, po.size()) {
    point u = po.vs[i], v = po.vs[po.next(i)];
    if (is_on_S({u, v}, p)) return RELPoP::onborder;
    if (!is_gt(u.y, v.y)) swap(u, v);
    if (is_gt(p.y, u.y) || !is_gt(p.y, v.y)) continue;
    result ^= sgn_cross(p, u, v) > 0;
  }
  retif_((result), RELPoP::inside, RELPoP::outside);
}

}  // namespace tifa_libs::geo

#endif