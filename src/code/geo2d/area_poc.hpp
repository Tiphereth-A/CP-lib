#ifndef TIFALIBS_GEO2D_AREA_POC
#define TIFALIBS_GEO2D_AREA_POC

#include "circle.hpp"
#include "polygon.hpp"
#include "sarea_ct.hpp"

namespace tifa_libs::geo {

template <class FP>
FP area_PoC(polygon<FP> const &po, circle<FP> const &c) {
  FP ans{};
  u32 sz = (u32)po.vs.size();
  if (sz < 3) return ans;
  for (u32 i = 0; i < sz; ++i) ans += sarea_CT(c, po[i], po[po.next(i)]);
  return std::abs(ans);
}

}  // namespace tifa_libs::geo

#endif