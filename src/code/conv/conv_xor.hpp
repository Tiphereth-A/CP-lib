#ifndef TIFALIBS_CONV_CONV_XOR
#define TIFALIBS_CONV_CONV_XOR

#include "wht.hpp"

namespace tifa_libs::math {

template <class T>
inline vec<T> conv_xor(vec<T> l, vec<T> r) {
  wht(l);
  wht(r);
  for (size_t i = 0; i < l.size(); ++i) l[i] *= r[i];
  iwht(l);
  return l;
}

}  // namespace tifa_libs::math

#endif