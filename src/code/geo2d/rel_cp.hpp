#ifndef TIFA_LIBS_GEO2D_REL_CP
#define TIFA_LIBS_GEO2D_REL_CP

#include "../util/util.hpp"
#include "circle_class.hpp"

#include "point.hpp"

namespace tifa_libs::geo2d {
// relation between circle and point
enum RELA_CP {
  outside_cp,
  onborder_cp,
  inside_cp,
};
constexpr RELA_CP relation_CP(const Circle &c, const Point &p) {
  data_t d = dist_PP(c.o, p);
  if (is_less(d, c.r)) return RELA_CP::inside_cp;
  if (is_equal(d, c.r)) return RELA_CP::onborder_cp;
  return RELA_CP::outside_cp;
}
}  // namespace tifa_libs::geo2d

#endif