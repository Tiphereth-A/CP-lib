#ifndef TIFALIBS_GEO2D_REL_CP
#define TIFALIBS_GEO2D_REL_CP

#include "circle.hpp"
#include "dist_pp.hpp"

namespace tifa_libs::geo {

// relation between circle and point
enum RELCP { outside_cp,
             onborder_cp,
             inside_cp };

template <class FP>
CEXP RELCP relation_CP(circle<FP> CR c, point<FP> CR p) {
  const FP d = dist_PP(c.o, p);
  if (is_lt(d, c.r)) return inside_cp;
  if (is_eq(d, c.r)) return onborder_cp;
  return outside_cp;
}

}  // namespace tifa_libs::geo

#endif