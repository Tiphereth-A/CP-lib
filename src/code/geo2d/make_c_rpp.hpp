#ifndef TIFA_LIBS_GEO2D_MAKE_C_RPP
#define TIFA_LIBS_GEO2D_MAKE_C_RPP

#include "ins_cc.hpp"

namespace tifa_libs::geo {

// make circle by radius and 2 point passed through
// maybe duplicate
template <class FP>
std::optional<ptt<circle<FP>>> make_C_rPP(FP r, point<FP> const &p1, point<FP> const &p2) {
  auto ps = ins_CC({p1, r}, {p2, r});
  if (!ps.has_value()) return {};
  return {{ps.value().first, r}, {ps.value().second, r}};
}

}  // namespace tifa_libs::geo

#endif