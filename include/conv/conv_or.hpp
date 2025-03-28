#ifndef TIFALIBS_CONV_CONV_OR
#define TIFALIBS_CONV_CONV_OR

#include "zmt_subset.hpp"

namespace tifa_libs::math {

template <class T>
CEXP vec<T> conv_or(vec<T> l, vec<T> r) NE {
  zt_subset(l), zt_subset(r);
  flt_ (u32, i, 0, (u32)l.size()) l[i] *= r[i];
  mt_subset(l);
  return l;
}

}  // namespace tifa_libs::math

#endif