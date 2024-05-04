#ifndef TIFALIBS_GEO2D_AREA_POC
#define TIFALIBS_GEO2D_AREA_POC

#include "../math/kahan.hpp"
#include "circle.hpp"
#include "polygon.hpp"
#include "sarea_ct.hpp"

namespace tifa_libs::geo {

template <class FP>
CEXP FP area_PoC(polygon<FP> CR po, circle<FP> CR c) {
  math::kahan<FP> ans{};
  u32 sz = (u32)po.vs.size();
  if (sz < 3) return ans;
  flt_ (u32, i, 0, sz) ans += sarea_CT(c, po[i], po[po.next(i)]);
  return abs<FP>(ans);
}

}  // namespace tifa_libs::geo

#endif