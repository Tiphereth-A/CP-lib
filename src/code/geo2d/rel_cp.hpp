#ifndef TIFA_LIBS_GEO2D_REL_CP
#define TIFA_LIBS_GEO2D_REL_CP

#include "circle.hpp"
#include "dist_pp.hpp"

namespace tifa_libs::geo {

// relation between circle and point
enum RELCP {
  outside_cp,
  onborder_cp,
  inside_cp,
};

template <class FP>
constexpr RELCP relation_CP(circle<FP> const &c, point<FP> const &p) {
  FP d = dist_PP(c.o, p);
  if (is_lt(d, c.r)) return inside_cp;
  if (is_eq(d, c.r)) return onborder_cp;
  return outside_cp;
}

}  // namespace tifa_libs::geo

#endif