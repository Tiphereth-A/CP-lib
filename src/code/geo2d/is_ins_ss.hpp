#ifndef TIFA_LIBS_GEO2D_IS_INS_SS
#define TIFA_LIBS_GEO2D_IS_INS_SS

#include "line.hpp"

namespace tifa_libs::geo {

// judge if two segments are intersected or not
//! containing endpoints
template <class FP>
constexpr bool is_ins_SS(line<FP> const &s1, line<FP> const &s2) { return is_intersect(s1.l.x, s1.r.x, s2.l.x, s2.r.x) && is_intersect(s1.l.y, s1.r.y, s2.l.y, s2.r.y) && sgn_cross(s1.l, s1.r, s2.l) * sgn_cross(s1.l, s1.r, s2.r) <= 0 && sgn_cross(s2.l, s2.r, s1.l) * sgn_cross(s2.l, s2.r, s1.r) <= 0; }
// judge if two segments are intersected or not
//! NOT containing endpoints
template <class FP>
constexpr bool is_ins_SS_strict(line<FP> const &s1, line<FP> const &s2) { return sgn_cross(s1.l, s1.r, s2.l) * sgn_cross(s1.l, s1.r, s2.r) < 0 && sgn_cross(s2.l, s2.r, s1.l) * sgn_cross(s2.l, s2.r, s1.r) < 0; }

}  // namespace tifa_libs::geo

#endif