#ifndef TIFA_LIBS_BIT_CNTL0
#define TIFA_LIBS_BIT_CNTL0

#include "../util/util.hpp"

namespace tifa_libs::bit {

// From GCC lib
template <typename T>
constexpr int cntl0(T x) {
  constexpr int nd = sizeof(T) * 8;
  if (x == 0) return nd;
  constexpr int nd_ull = sizeof(unsigned long long) * 8;
  constexpr int nd_ul = sizeof(unsigned long) * 8;
  constexpr int nd_u = sizeof(unsigned) * 8;
  if constexpr (nd <= nd_u)
    return __builtin_clz(x) - (nd_u - nd);
  else if constexpr (nd <= nd_ul)
    return __builtin_clzl(x) - (nd_ul - nd);
  else if constexpr (nd <= nd_ull)
    return __builtin_clzll(x) - (nd_ull - nd);
  else {
    static_assert(nd <= (2 * nd_ull), "Maximum supported integer size is 128-bit");
    unsigned long long hi = x >> nd_ull;
    if (hi != 0) return __builtin_clzll(hi) - ((2 * nd_ull) - nd);
    unsigned long long lo = x & (unsigned long long)(-1);
    return (nd - nd_ull) + __builtin_clzll(lo);
  }
}

}  // namespace tifa_libs::bit

#endif