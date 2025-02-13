#ifndef TIFALIBS_GEO2D_MASSP
#define TIFALIBS_GEO2D_MASSP

#include "../math/kahan.hpp"
#include "cross.hpp"
#include "point.hpp"

namespace tifa_libs::geo {

template <class FP>
CEXP point<FP> massp(vec<point<FP>> CR vp) NE {
  point<FP> ret{};
  math::kahan<FP> area{};
  u32 n = (u32)vp.size();
  if (n == 0) return ret;
  if (n == 1) return vp[0];
  flt_ (u32, i, 1, n - 1) {
    const FP _ = cross(vp[0], vp[i], vp[i + 1]);
    if (!is_zero(_)) area += _, ret += (vp[0] + vp[i] + vp[i + 1]) * (_ / 3);
  }
  if (!is_zero<FP>(area)) ret /= (FP)area;
  return ret;
}

}  // namespace tifa_libs::geo

#endif