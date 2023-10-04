#ifndef TIFA_LIBS_GEO2D_REL_CC
#define TIFA_LIBS_GEO2D_REL_CC

#include "circle_class.hpp"

#include "point.hpp"

namespace tifa_libs::geo2d {

// relation between circle and circle
enum RELA_CC {
  lyingin_cc,
  touchin_cc,
  intersect_cc,
  touchex_cc,
  lyingout_cc
};

template <class FP>
constexpr RELA_CC relation_CC(circle<FP> const &c, circle<FP> const &c2) {
  FP d = dist_PP(c.o, c2.o);
  if (is_ge(d, c.r + c2.r)) return RELA_CC::lyingout_cc;
  if (is_eq(d, c.r + c2.r)) return RELA_CC::touchex_cc;
  if (is_ge(d, std::abs(c.r - c2.r))) return RELA_CC::intersect_cc;
  if (is_eq(d, std::abs(c.r - c2.r))) return RELA_CC::touchin_cc;
  return RELA_CC::lyingin_cc;
}

}  // namespace tifa_libs::geo2d

#endif