#ifndef TIFALIBS_GEO2D_POLY_CNT_INTP
#define TIFALIBS_GEO2D_POLY_CNT_INTP

#include "../util/fp2uint.hpp"
#include "polygon.hpp"

namespace tifa_libs::geo {

// Count of integer point on the border of polygon
template <class FP>
u64 poly_cnt_intP_border(polygon<FP> const &po) {
  u64 ret = 0;
  for (u32 i = 0; i < (u32)po.vs.size(); ++i) ret += std::gcd(fp2uint(std::abs(po.vs[i].x - po.vs[po.next(i)].x), EPS<FP>), fp2uint(std::abs(po.vs[i].y - po.vs[po.next(i)].y), EPS<FP>));
  return ret;
}
// Count of integer point in the polygon, based on Pick theorem
template <class FP>
u64 poly_cnt_intP_inner(polygon<FP> const &po) { return fp2uint(po.area(), EPS<FP>) - cnt_intP_border(po) / 2 + 1; }

}  // namespace tifa_libs::geo

#endif