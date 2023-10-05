#ifndef TIFA_LIBS_GEO2D_MAKE_C_RCC_EX
#define TIFA_LIBS_GEO2D_MAKE_C_RCC_EX

#include "ins_cc.hpp"
#include "rel_cc.hpp"

namespace tifa_libs::geo {

// make circle by radius and 2 external tagante circle
// maybe duplicate
template <class FP>
std::optional<ptt<circle<FP>>> make_C_rCC_ex(FP r, circle<FP> const &c1, circle<FP> const &c2) {
  if (relation_CC(c1, c2) == RELCC::lyingin_cc) return {};
  auto ps = ins_CC({c1.o, c1.r + r}, {c2.o, c2.r + r});
  if (!ps.has_value()) return {};
  return {{ps.value().first, r}, {ps.value().second, r}};
}

}  // namespace tifa_libs::geo

#endif