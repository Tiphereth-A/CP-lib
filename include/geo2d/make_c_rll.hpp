#ifndef TIFALIBS_GEO2D_MAKE_C_RLL
#define TIFALIBS_GEO2D_MAKE_C_RLL

#include "circle.hpp"
#include "ins_ll.hpp"

namespace tifa_libs::geo {

// make circle by radius and 2 tagante lines
template <class FP>
CEXP auto make_C_rLL(FP r, line<FP> CR l1, line<FP> CR l2) NE {
  std::optional<pt4<circle<FP>>> ret;
  if (is_parallel(l1, l2)) return ret;
  point<FP> dir1 = l1.direction(), dir2 = l2.direction();
  dir1 *= r / dir1.norm(), dir2 *= r / dir2.norm();
  const point<FP> dirl1 = rot90(dir1), dirr1 = rot270(dir1),
                  dirl2 = rot90(dir2), dirr2 = rot270(dir2);
  const line<FP> u1 = {l1.l + dirl1, l1.r + dirl1}, u2 = {l1.l + dirr1, l1.r + dirr1},
                 v1 = {l2.l + dirl2, l2.r + dirl2}, v2 = {l2.l + dirr2, l2.r + dirr2};
  ret.emplace(circle{ins_LL(u1, v1), r}, circle{ins_LL(u1, v2), r}, circle{ins_LL(u2, v1), r}, circle{ins_LL(u2, v2), r});
  return ret;
}

}  // namespace tifa_libs::geo

#endif