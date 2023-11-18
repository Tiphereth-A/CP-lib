#ifndef TIFALIBS_CONV_CONV_AND
#define TIFALIBS_CONV_CONV_AND

#include "zmt_supset.hpp"

namespace tifa_libs::math {

template <class T>
vec<T> conv_and(vec<T> l, vec<T> r) {
  zt_supset(l);
  zt_supset(r);
  for (u32 i = 0; i < l.size(); ++i) l[i] *= r[i];
  mt_supset(l);
  return l;
}

}  // namespace tifa_libs::math

#endif