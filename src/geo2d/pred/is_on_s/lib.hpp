#ifndef TIFALIBS_GEO2D_PRED_IS_ON_S_LIB
#define TIFALIBS_GEO2D_PRED_IS_ON_S_LIB

#include "../../ds/l/lib.hpp"
#include "../is_in_middle_p/lib.hpp"
#include "../is_on_same_l/lib.hpp"

namespace tifa_libs::geo {

template <class FP, bool contain_endpoints = true>
CEXP bool is_on_S(line<FP> CR s, point<FP> CR p) NE {
  if CEXP (contain_endpoints) return is_on_same_L(s.l, s.r, p) && is_in_middle(s.l, p, s.r);
  else return s.toleft(p) == 0 && sgn((p - s.l) * (s.l - s.r)) * sgn((p - s.r) * (s.l - s.r)) < 0;
}

}  // namespace tifa_libs::geo

#endif