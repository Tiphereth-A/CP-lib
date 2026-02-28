#ifndef TIFALIBS_CONV_AND_LIB
#define TIFALIBS_CONV_AND_LIB

#include "../trans/zmt_supset/lib.hpp"

namespace tifa_libs::math {

template <class T>
CEXP vec<T> conv_and(vec<T> l, vec<T> r) NE {
  zt_supset(l), zt_supset(r);
  flt_ (u32, i, 0, (u32)l.size()) l[i] *= r[i];
  mt_supset(l);
  return l;
}

}  // namespace tifa_libs::math

#endif