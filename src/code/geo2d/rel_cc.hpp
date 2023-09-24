#ifndef TIFA_LIBS_GEO2D_REL_CC
#define TIFA_LIBS_GEO2D_REL_CC

#include "../util/util.hpp"
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
constexpr RELA_CC relation_CC(const Circle &c, const Circle &c2) {
  data_t d = dist_PP(c.o, c2.o);
  if (is_greater(d, c.r + c2.r)) return RELA_CC::lyingout_cc;
  if (is_equal(d, c.r + c2.r)) return RELA_CC::touchex_cc;
  if (is_greater(d, std::abs(c.r - c2.r))) return RELA_CC::intersect_cc;
  if (is_equal(d, std::abs(c.r - c2.r))) return RELA_CC::touchin_cc;
  return RELA_CC::lyingin_cc;
}
}  // namespace tifa_libs::geo2d

#endif