#ifndef TIFA_LIBS_GEO2D_REL_CC
#define TIFA_LIBS_GEO2D_REL_CC

#include "circle.hpp"
#include "point.hpp"

namespace tifa_libs::geo2d {

// relation between circle and circle
enum RELCC {
  lyingin_cc,
  touchin_cc,
  intersect_cc,
  touchex_cc,
  lyingout_cc
};

template <class FP>
constexpr RELCC relation_CC(circle<FP> const &c, circle<FP> const &c2) {
  FP d = dist_PP(c.o, c2.o);
  if (is_ge(d, c.r + c2.r)) return RELCC::lyingout_cc;
  if (is_eq(d, c.r + c2.r)) return RELCC::touchex_cc;
  if (is_ge(d, std::abs(c.r - c2.r))) return RELCC::intersect_cc;
  if (is_eq(d, std::abs(c.r - c2.r))) return RELCC::touchin_cc;
  return RELCC::lyingin_cc;
}

}  // namespace tifa_libs::geo2d

#endif