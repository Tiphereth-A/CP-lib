#ifndef TIFALIBS_GEO2D_PRED_IS_INS_SL_LIB
#define TIFALIBS_GEO2D_PRED_IS_INS_SL_LIB

#include "../../ds/l/lib.hpp"

namespace tifa_libs::geo {

// judge if segment and line are intersected
template <class FP, bool contain_endpoints = true>
CEXP bool is_ins_SL(line<FP> CR s, line<FP> CR l) NE {
  const auto a = l.toleft(s.l), b = l.toleft(s.r);
  if CEXP (contain_endpoints) return !a || !b || a != b;
  else return a && b && !(a + b);
}

}  // namespace tifa_libs::geo

#endif