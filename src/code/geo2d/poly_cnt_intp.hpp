#ifndef TIFA_LIBS_GEO2D_POLY_CNT_INTP
#define TIFA_LIBS_GEO2D_POLY_CNT_INTP

#include "../util/fp2uint.hpp"
#include "polygon.hpp"

namespace tifa_libs::geo2d {

// Count of integer point on the border of polygon
template <class FP>
u64 poly_cnt_intP_border(polygon<FP> const &poly) {
  u64 ret = 0;
  for (size_t i = 0; i < poly.vs.size(); ++i) ret += std::gcd(fp2uint(std::abs(poly.vs[i].x - poly.vs[poly.next(i)].x), EPS), fp2uint(std::abs(poly.vs[i].y - poly.vs[poly.next(i)].y), EPS));
  return ret;
}
// Count of integer point in the polygon, based on Pick theorem
template <class FP>
u64 poly_cnt_intP_inner(polygon<FP> const &poly) { return fp2uint(poly.area(), EPS) - cnt_intP_border(poly) / 2 + 1; }

}  // namespace tifa_libs::geo2d

#endif