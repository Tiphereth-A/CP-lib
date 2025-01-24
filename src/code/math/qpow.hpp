#ifndef TIFALIBS_MATH_QPOW
#define TIFALIBS_MATH_QPOW

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class T>
CEXP T qpow(T a, u64 b, cT_(T) init_v = T{1}) NE {
  T res = init_v;
  for (; b; b >>= 1, a = a * a) {
    while (!(b & 1)) b >>= 1, a = a * a;
    res = res * a;
  }
  return res;
}

}  // namespace tifa_libs::math

#endif