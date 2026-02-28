#ifndef TIFALIBS_GEO2D_MAKE_C_PCC_EX_LIB
#define TIFALIBS_GEO2D_MAKE_C_PCC_EX_LIB

#include "../../../edh/discretization/lib.hpp"
#include "../../inv/c2c/lib.hpp"
#include "../../inv/l2c/lib.hpp"
#include "../../pred/is_on_same_l/lib.hpp"
#include "../../rel/cc/lib.hpp"
#include "../../rel/cp/lib.hpp"
#include "../../tan/cc_ex/lib.hpp"
#include "../../tan/cc_in/lib.hpp"

namespace tifa_libs::geo {

// make circle by point passed through and 2 external tagante circle
// result size: 0 to 4
template <class FP>
CEXP vec<circle<FP>> make_C_PCC_ex(point<FP> CR p, circle<FP> c1, circle<FP> c2) NE {
  if (relation_CC(c1, c2) == RELCC::lyingin ||
      relation_CP(c1, p) != RELCP::outside ||
      relation_CP(c2, p) != RELCP::outside) return {};
  vec<line<FP>> vl;
  if (auto _ = intan_CC(c1 = inv_C2C(p, c1), c2 = inv_C2C(p, c2)); _) {
    auto CR[l1, l2] = _.value();
    if (!is_on_same_L(p, l1.l, l1.r)) vl.push_back(l1);
    if (!is_on_same_L(p, l2.l, l2.r)) vl.push_back(l2);
  }
  if (auto _ = extan_CC(c1, c2); _) {
    auto CR[l1, l2] = _.value();
    if (!is_on_same_L(p, l1.l, l1.r)) vl.push_back(l1);
    if (!is_on_same_L(p, l2.l, l2.r)) vl.push_back(l2);
  }
  vec<circle<FP>> vc;
  for (uniq(vl); auto CR l : vl) vc.push_back(inv_L2C(p, l));
  return vc;
}

}  // namespace tifa_libs::geo

#endif