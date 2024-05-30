#ifndef TIFALIBS_GEO2D_IS_INS_SL
#define TIFALIBS_GEO2D_IS_INS_SL

#include "line.hpp"

namespace tifa_libs::geo {

// judge if segment and line are intersected
//! containing endpoints
template <class FP>
CEXP bool is_ins_SL(line<FP> CR s, line<FP> CR l) {
  const auto a = l.toleft(s.l), b = l.toleft(s.r);
  return !a || !b || a != b;
}
// judge if segment and line are intersected
//! NOT containing endpoints
template <class FP>
CEXP bool is_ins_SL_strict(line<FP> CR s, line<FP> CR l) {
  const auto a = l.toleft(s.l), b = l.toleft(s.r);
  return a && b && !(a + b);
}

}  // namespace tifa_libs::geo

#endif