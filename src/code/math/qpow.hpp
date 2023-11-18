#ifndef TIFA_LIBS_MATH_QPOW
#define TIFA_LIBS_MATH_QPOW

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class T>
constexpr T qpow(T a, u64 b, T const& init_v = T{1}) {
  T res(init_v);
  for (; b; b >>= 1, a = a * a)
    if (b & 1) res = res * a;
  return res;
}

}  // namespace tifa_libs::math

#endif