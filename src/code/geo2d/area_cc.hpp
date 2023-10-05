#ifndef TIFA_LIBS_GEO2D_AREA_CC
#define TIFA_LIBS_GEO2D_AREA_CC

#include "circle.hpp"
#include "rel_cc.hpp"

namespace tifa_libs::geo {

template <class FP>
constexpr FP area_CC(circle<FP> const &c1, circle<FP> const &c2) {
  auto relation = relation_CC(c1, c2);
  if (relation == RELCC::lyingout_cc || relation == RELCC::touchex_cc) return FP{};
  if (relation == RELCC::lyingin_cc || relation == RELCC::touchin_cc) return std::min(
    c1.area(), c2.area());
  FP d = dist_PP(c1.o, c2.o);
  return c1.crown_area(std::acos((c1.r * c1.r - c2.r * c2.r + d * d) / (2 * c1.r * d)) * 2) + c2.crown_area(std::acos((c2.r * c2.r - c1.r * c1.r + d * d) / (2 * c2.r * d)) * 2);
}

}  // namespace tifa_libs::geo

#endif