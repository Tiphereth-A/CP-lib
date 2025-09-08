#ifndef TIFALIBS_GEO2D_MAKE_C_RPP
#define TIFALIBS_GEO2D_MAKE_C_RPP

#include "ins_cc.hpp"

namespace tifa_libs::geo {

// make circle by radius and 2 point passed through
// maybe duplicate
template <class FP>
CEXP auto make_C_rPP(FP r, point<FP> CR p1, point<FP> CR p2) NE {
  std::optional<ptt<circle<FP>>> ret;
  auto CR ps = ins_CC({p1, r}, {p2, r});
  if (!ps) return ret;
  ret.emplace({ps->first, r}, {ps->second, r});
  return ret;
}

}  // namespace tifa_libs::geo

#endif