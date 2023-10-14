#ifndef TIFALIBS_CONV_CONV_XOR
#define TIFALIBS_CONV_CONV_XOR

#include "wht.hpp"

namespace tifa_libs::math {

template <class T>
inline vec<T> conv_xor(vec<T> l, vec<T> r) {
  wht_dif(l);
  wht_dif(r);
  for (size_t i = 0; i < l.size(); ++i) l[i] *= r[i];
  wht_dit(l);
  return l;
}

}  // namespace tifa_libs::math

#endif