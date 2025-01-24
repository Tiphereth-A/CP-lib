#ifndef TIFALIBS_GEO2D_INS_LL
#define TIFALIBS_GEO2D_INS_LL

#include "line.hpp"

namespace tifa_libs::geo {

// judge if two lines are intersected or not
template <class FP>
CEXP bool is_ins_LL(line<FP> CR l1, line<FP> CR l2) NE { return !is_zero(cross(l2.l, l2.r, l1.l) - cross(l2.l, l2.r, l1.r)); }
// intersection point of two lines
template <class FP>
CEXP point<FP> ins_LL(line<FP> CR l1, line<FP> CR l2) NE {
  const FP a1 = cross(l2.l, l2.r, l1.l), a2 = -cross(l2.l, l2.r, l1.r);
  return (l1.l * a2 + l1.r * a1) / (a1 + a2);
}
template <class FP>
CEXP point<FP> ins_LL(line<FP> CR l, FP a, FP b, FP c) NE {
  const FP a1 = abs(a * l.l.x + b * l.l.y + c), a2 = abs(a * l.r.x + b * l.r.y + c);
  return (l.l * a2 + l.r * a1) / (a1 + a2);
}

}  // namespace tifa_libs::geo

#endif