#ifndef TIFALIBS_GEO2D_MAKE_C_RPP
#define TIFALIBS_GEO2D_MAKE_C_RPP

#include "ins_cc.hpp"

namespace tifa_libs::geo {

// make circle by radius and 2 point passed through
// maybe duplicate
template <class FP>
CEXP std::optional<ptt<circle<FP>>> make_C_rPP(FP r, point<FP> CR p1, point<FP> CR p2) NE {
  if (auto CR ps = ins_CC({p1, r}, {p2, r}); !ps.has_value()) return {};
  else return {{ps.value().first, r}, {ps.value().second, r}};
}

}  // namespace tifa_libs::geo

#endif