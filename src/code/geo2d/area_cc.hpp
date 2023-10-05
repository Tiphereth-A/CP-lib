#ifndef TIFA_LIBS_GEO2D_AREA_CC
#define TIFA_LIBS_GEO2D_AREA_CC

#include "circle.hpp"
#include "rel_cc.hpp"

namespace tifa_libs::geo {

template <class FP>
constexpr FP area_CC(circle<FP> const &lhs, circle<FP> const &rhs) {
  auto relation = relation_CC(lhs, rhs);
  if (relation == RELCC::lyingout_cc || relation == RELCC::touchex_cc) return FP{};
  if (relation == RELCC::lyingin_cc || relation == RELCC::touchin_cc) return std::min(
    lhs.area(), rhs.area());
  FP d = dist_PP(lhs.o, rhs.o);
  return lhs.crown_area(std::acos((lhs.r * lhs.r - rhs.r * rhs.r + d * d) / (2 * lhs.r * d)) * 2) + rhs.crown_area(std::acos((rhs.r * rhs.r - lhs.r * lhs.r + d * d) / (2 * rhs.r * d)) * 2);
}

}  // namespace tifa_libs::geo

#endif