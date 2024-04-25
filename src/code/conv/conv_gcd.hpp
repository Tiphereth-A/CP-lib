#ifndef TIFALIBS_CONV_CONV_GCD
#define TIFALIBS_CONV_CONV_GCD

#include "zmt_multiple.hpp"

namespace tifa_libs::math {

template <class T>
CEXP vec<T> conv_gcd(vec<T> l, vec<T> r) {
  assert(l.size() == r.size());
  auto pf = prime_seq((u32)l.size() - 1);
  zt_multiple(l, pf);
  zt_multiple(r, pf);
  for (u32 i = 0; i < l.size(); ++i) l[i] *= r[i];
  mt_multiple(l, pf);
  return l;
}

}  // namespace tifa_libs::math

#endif