#ifndef TIFA_LIBS_GEO2D_REL_CP
#define TIFA_LIBS_GEO2D_REL_CP

#include "circle_class.hpp"

#include "point.hpp"

namespace tifa_libs::geo2d {

// relation between circle and point
enum RELCP {
  outside_cp,
  onborder_cp,
  inside_cp,
};

template <class FP>
constexpr RELCP relation_CP(circle<FP> const &c, point<FP> const &p) {
  FP d = dist_PP(c.o, p);
  if (is_le(d, c.r)) return RELCP::inside_cp;
  if (is_eq(d, c.r)) return RELCP::onborder_cp;
  return RELCP::outside_cp;
}

}  // namespace tifa_libs::geo2d

#endif