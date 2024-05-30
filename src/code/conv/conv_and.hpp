#ifndef TIFALIBS_CONV_CONV_AND
#define TIFALIBS_CONV_CONV_AND

#include "zmt_supset.hpp"

namespace tifa_libs::math {

template <class T>
CEXP vec<T> conv_and(vec<T> l, vec<T> r) {
  zt_supset(l), zt_supset(r);
  flt_ (u32, i, 0, (u32)l.size()) l[i] *= r[i];
  mt_supset(l);
  return l;
}

}  // namespace tifa_libs::math

#endif