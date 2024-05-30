#ifndef TIFALIBS_CONV_CONV_LCM
#define TIFALIBS_CONV_CONV_LCM

#include "zmt_divisor.hpp"

namespace tifa_libs::math {

template <class T>
CEXP vec<T> conv_lcm(vec<T> l, vec<T> r) {
  assert(l.size() == r.size());
  const auto pf = prime_seq((u32)l.size() - 1);
  zt_divisor(l, pf), zt_divisor(r, pf);
  flt_ (u32, i, 0, (u32)l.size()) l[i] *= r[i];
  mt_divisor(l, pf);
  return l;
}

}  // namespace tifa_libs::math

#endif