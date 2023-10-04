#ifndef TIFA_LIBS_GEO2D_IS_INS_SS
#define TIFA_LIBS_GEO2D_IS_INS_SS

#include "line.hpp"

namespace tifa_libs::geo2d {

// judge if two segments are intersected or not
//! containing endpoints
template <class FP>
constexpr bool is_ins_SS(line<FP> const &l1, line<FP> const &l2) { return is_intersect(l1.l.x, l1.r.x, l2.l.x, l2.r.x) && is_intersect(l1.l.y, l1.r.y, l2.l.y, l2.r.y) && sgn_cross(l1.l, l1.r, l2.l) * sgn_cross(l1.l, l1.r, l2.r) <= 0 && sgn_cross(l2.l, l2.r, l1.l) * sgn_cross(l2.l, l2.r, l1.r) <= 0; }
// judge if two segments are intersected or not
//! NOT containing endpoints
template <class FP>
constexpr bool is_ins_SS_strict(line<FP> const &s1, line<FP> const &s2) { return sgn_cross(s1.l, s1.r, s2.l) * sgn_cross(s1.l, s1.r, s2.r) < 0 && sgn_cross(s2.l, s2.r, s1.l) * sgn_cross(s2.l, s2.r, s1.r) < 0; }

}  // namespace tifa_libs::geo2d

#endif