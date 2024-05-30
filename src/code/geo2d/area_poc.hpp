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
  const u32 n = po.size();
  if (n < 3) return ans;
  flt_ (u32, i, 0, n) ans += sarea_CT(c, po[i], po[po.next(i)]);
  return abs<FP>(ans);
}

}  // namespace tifa_libs::geo

#endif