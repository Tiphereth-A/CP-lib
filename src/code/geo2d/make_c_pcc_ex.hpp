#ifndef TIFALIBS_GEO2D_MAKE_C_PCC_EX
#define TIFALIBS_GEO2D_MAKE_C_PCC_EX

#include "../edh/discretization.hpp"
#include "extan_cc.hpp"
#include "intan_cc.hpp"
#include "inv_c2c.hpp"
#include "inv_l2c.hpp"
#include "is_on_same_l.hpp"
#include "rel_cc.hpp"
#include "rel_cp.hpp"

namespace tifa_libs::geo {

// make circle by point passed through and 2 external tagante circle
// result size: 0 to 4
template <class FP>
CEXP vec<circle<FP>> make_C_PCC_ex(point<FP> CR p, circle<FP> c1, circle<FP> c2) {
  if (relation_CC(c1, c2) == lyingin_cc || relation_CP(c1, p) != outside_cp || relation_CP(c2, p) != outside_cp) return {};
  vec<line<FP>> vl;
  if (auto _ = intan_CC(c1 = inv_C2C(p, c1), c2 = inv_C2C(p, c2)); _.has_value()) {
    auto &&[l1, l2] = _.value();
    if (!is_on_same_L(p, l1.l, l1.r)) vl.push_back(l1);
    if (!is_on_same_L(p, l2.l, l2.r)) vl.push_back(l2);
  }
  if (auto _ = extan_CC(c1, c2); _.has_value()) {
    auto &&[l1, l2] = _.value();
    if (!is_on_same_L(p, l1.l, l1.r)) vl.push_back(l1);
    if (!is_on_same_L(p, l2.l, l2.r)) vl.push_back(l2);
  }
  uniq(vl);
  vec<circle<FP>> vc;
  for (auto CR l : vl) vc.push_back(inv_L2C(p, l));
  return vc;
}

}  // namespace tifa_libs::geo

#endif