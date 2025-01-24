#ifndef TIFALIBS_GEO2D_AREA_CC
#define TIFALIBS_GEO2D_AREA_CC

#include "circle.hpp"
#include "rel_cc.hpp"

namespace tifa_libs::geo {

template <class FP>
CEXP FP area_CC(circle<FP> CR c1, circle<FP> CR c2) NE {
  const auto relation = relation_CC(c1, c2);
  if (relation == lyingout_cc || relation == touchex_cc) return FP{};
  if (relation == lyingin_cc || relation == touchin_cc) return min(c1.area(), c2.area());
  const FP d = dist_PP(c1.o, c2.o);
  return c1.crown_area(std::acos((c1.r * c1.r - c2.r * c2.r + d * d) / (2 * c1.r * d)) * 2) +
         c2.crown_area(std::acos((c2.r * c2.r - c1.r * c1.r + d * d) / (2 * c2.r * d)) * 2);
}

}  // namespace tifa_libs::geo

#endif