#ifndef TIFALIBS_GEO2D_AINS_POC_LIB
#define TIFALIBS_GEO2D_AINS_POC_LIB

#include "../../../math/kahan/lib.hpp"
#include "../../ds/c/lib.hpp"
#include "../../ds/po/lib.hpp"
#include "../ct_s/lib.hpp"

namespace tifa_libs::geo {

template <class FP>
CEXP FP area_PoC(polygon<FP> CR po, circle<FP> CR c) NE {
  math::kahan<FP> ans{};
  const u32 n = po.size();
  retif_((n < 3) [[unlikely]], ans);
  flt_ (u32, i, 0, n) ans += sarea_CT(c, po[i], po[po.next(i)]);
  return abs<FP>(ans);
}

}  // namespace tifa_libs::geo

#endif