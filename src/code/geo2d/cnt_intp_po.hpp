#ifndef TIFALIBS_GEO2D_CNT_INTP_PO
#define TIFALIBS_GEO2D_CNT_INTP_PO

#include "../nt/gcd.hpp"
#include "polygon.hpp"

namespace tifa_libs::geo {

// Count of integer point on the border of polygon
template <int_c FP>
CEXP u64 cnt_intP_border_po(polygon<FP> CR po) {
  u64 ret = 0;
  flt_ (u32, i, 0, po.size()) ret += math::gcd(abs(po.vs[i].x - po.vs[po.next(i)].x), abs(po.vs[i].y - po.vs[po.next(i)].y));
  return ret;
}
// Count of integer point in the polygon, based on Pick theorem
template <int_c FP>
CEXP u64 cnt_intP_inner_po(polygon<FP> CR po) { return (po.area2() - cnt_intP_border(po) + 2) / 2; }

}  // namespace tifa_libs::geo

#endif