#ifndef TIFALIBS_CONV_XOR_LIB
#define TIFALIBS_CONV_XOR_LIB

#include "../trans/wht/lib.hpp"

namespace tifa_libs::math {

template <class T>
CEXP vec<T> conv_xor(vec<T> l, vec<T> r) NE {
  wht(l), wht(r);
  flt_ (u32, i, 0, (u32)l.size()) l[i] *= r[i];
  iwht(l);
  return l;
}

}  // namespace tifa_libs::math

#endif