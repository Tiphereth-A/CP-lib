#ifndef TIFA_LIBS_GEO2D_MAKE_C_RLL
#define TIFA_LIBS_GEO2D_MAKE_C_RLL

#include "circle.hpp"
#include "line.hpp"

namespace tifa_libs::geo2d {

// make circle by radius and 2 tagante lines
template <class FP>
std::optional<pt4<circle<FP>>> make_C_rLL(FP r, line<FP> const &l1, line<FP> const &l2) {
  if (is_parallel(l1, l2)) return {};
  point<FP> dir1 = l1.direction(), dir2 = l2.direction();
  dir1 *= r / dir1.norm();
  dir2 *= r / dir2.norm();
  point<FP> dirl1 = rot90(dir1), dirr1 = rot270(dir1), dirl2 = rot90(dir2), dirr2 = rot270(dir2);
  line<FP> u1 = {l1.l + dirl1, l1.r + dirl1}, u2 = {l1.l + dirr1, l1.r + dirr1}, v1 = {l2.l + dirl2, l2.r + dirl2}, v2 = {l2.l + dirr2, l2.r + dirr2};
  return {{ins_LL(u1, v1), r}, {ins_LL(u1, v2), r}, {ins_LL(u2, v1), r}, {ins_LL(u2, v2), r}};
}

}  // namespace tifa_libs::geo2d

#endif