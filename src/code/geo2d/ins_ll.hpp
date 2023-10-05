#ifndef TIFA_LIBS_GEO2D_INS_LL
#define TIFA_LIBS_GEO2D_INS_LL

#include "line.hpp"

namespace tifa_libs::geo {

// judge if two lines are intersected or not
template <class FP>
constexpr bool is_ins_LL(line<FP> const &l1, line<FP> const &l2) { return !is_zero(cross(l2.l, l2.r, l1.l) - cross(l2.l, l2.r, l1.r)); }
// intersection point of two lines
template <class FP>
constexpr point<FP> ins_LL(line<FP> const &l1, line<FP> const &l2) {
  FP a1 = cross(l2.l, l2.r, l1.l), a2 = -cross(l2.l, l2.r, l1.r);
  return (l1.l * a2 + l1.r * a1) / (a1 + a2);
}

}  // namespace tifa_libs::geo

#endif