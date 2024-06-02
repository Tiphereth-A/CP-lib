#ifndef TIFALIBS_GEO2D_REL_CC
#define TIFALIBS_GEO2D_REL_CC

#include "circle.hpp"
#include "dist_pp.hpp"

namespace tifa_libs::geo {

// relation between circle and circle
enum RELCC { lyingin_cc,
             touchin_cc,
             intersect_cc,
             touchex_cc,
             lyingout_cc };

template <class FP>
CEXP RELCC relation_CC(circle<FP> CR c1, circle<FP> CR c2) {
  const FP d = dist_PP(c1.o, c2.o);
  if (is_gt(d, c1.r + c2.r)) return lyingout_cc;
  if (is_eq(d, c1.r + c2.r)) return touchex_cc;
  if (is_gt(d, abs(c1.r - c2.r))) return intersect_cc;
  if (is_eq(d, abs(c1.r - c2.r))) return touchin_cc;
  return lyingin_cc;
}

}  // namespace tifa_libs::geo

#endif