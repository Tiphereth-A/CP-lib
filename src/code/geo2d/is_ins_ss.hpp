#ifndef TIFALIBS_GEO2D_IS_INS_SS
#define TIFALIBS_GEO2D_IS_INS_SS

#include "line.hpp"

namespace tifa_libs::geo {

// judge if two segments are intersected
//! containing endpoints
template <class FP>
CEXP bool is_ins_SS(line<FP> CR s1, line<FP> CR s2) { return is_intersect(s1.l.x, s1.r.x, s2.l.x, s2.r.x) && is_intersect(s1.l.y, s1.r.y, s2.l.y, s2.r.y) && s1.toleft(s2.l) * s1.toleft(s2.r) <= 0 && s2.toleft(s1.l) * s2.toleft(s1.r) <= 0; }
// judge if two segments are intersected
//! NOT containing endpoints
template <class FP>
CEXP bool is_ins_SS_strict(line<FP> CR s1, line<FP> CR s2) { return s1.toleft(s2.l) * s1.toleft(s2.r) < 0 && s2.toleft(s1.l) * s2.toleft(s1.r) < 0; }

}  // namespace tifa_libs::geo

#endif