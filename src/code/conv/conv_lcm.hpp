#ifndef TIFALIBS_CONV_CONV_LCM
#define TIFALIBS_CONV_CONV_LCM

#include "zmt_divisor.hpp"

namespace tifa_libs::math {

template <class T>
inline vec<T> conv_lcm(vec<T> l, vec<T> r) {
  assert(l.size() == r.size());
  auto pf = linear_p_seive((u32)l.size() - 1);
  zt_divisor(l, pf);
  zt_divisor(r, pf);
  for (usz i = 0; i < l.size(); ++i) l[i] *= r[i];
  mt_divisor(l, pf);
  return l;
}

}  // namespace tifa_libs::math

#endif