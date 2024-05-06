#ifndef TIFALIBS_GEO2D_MASSP
#define TIFALIBS_GEO2D_MASSP

#include "polygon.hpp"

namespace tifa_libs::geo {

template <class FP>
CEXP point<FP> massp(polygon<FP> CR po) {
  point<FP> ret{};
  math::kahan<FP> area{};
  u32 n = po.size();
  if (n == 0) return ret;
  if (n == 1) return po.vs[0];
  for (u32 i = 1; i < n - 1; ++i) {
    FP _ = cross(po.vs[0], po.vs[i], po.vs[i + 1]);
    if (is_zero(_)) continue;
    area += _;
    ret += (po.vs[0] + po.vs[i] + po.vs[i + 1]) * (_ / 3);
  }
  if (!is_zero<FP>(area)) ret /= (FP)area;
  return ret;
}

}  // namespace tifa_libs::geo

#endif