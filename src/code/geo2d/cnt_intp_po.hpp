#ifndef TIFALIBS_GEO2D_CNT_INTP_PO
#define TIFALIBS_GEO2D_CNT_INTP_PO

#include "../nt/gcd.hpp"
#include "../util/fp2uint.hpp"
#include "polygon.hpp"

namespace tifa_libs::geo {

// Count of integer point on the border of polygon
template <class FP>
CEXP u64 cnt_intP_border_po(polygon<FP> CR po) {
  u64 ret = 0;
  for (u32 i = 0; i < (u32)po.vs.size(); ++i) ret += math::gcd(fp2uint(abs(po.vs[i].x - po.vs[po.next(i)].x), eps_v<FP>), fp2uint(abs(po.vs[i].y - po.vs[po.next(i)].y), eps_v<FP>));
  return ret;
}
// Count of integer point in the polygon, based on Pick theorem
template <class FP>
CEXP u64 cnt_intP_inner_po(polygon<FP> CR po) { return fp2uint(po.area(), eps_v<FP>) - cnt_intP_border(po) / 2 + 1; }

}  // namespace tifa_libs::geo

#endif