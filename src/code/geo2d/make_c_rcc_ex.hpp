#ifndef TIFALIBS_GEO2D_MAKE_C_RCC_EX
#define TIFALIBS_GEO2D_MAKE_C_RCC_EX

#include "ins_cc.hpp"
#include "rel_cc.hpp"

namespace tifa_libs::geo {

// make circle by radius and 2 external tagante circle
// maybe duplicate
template <class FP>
CEXP std::optional<ptt<circle<FP>>> make_C_rCC_ex(FP r, circle<FP> CR c1, circle<FP> CR c2) NE {
  if (relation_CC(c1, c2) == lyingin_cc) return {};
  if (auto CR ps = ins_CC<FP>({c1.o, c1.r + r}, {c2.o, c2.r + r}); !ps.has_value()) return {};
  else return ptt<circle<FP>>{{ps.value().first, r}, {ps.value().second, r}};
}

}  // namespace tifa_libs::geo

#endif