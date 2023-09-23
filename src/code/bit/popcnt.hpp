#ifndef TIFA_LIBS_BIT_POPCNT
#define TIFA_LIBS_BIT_POPCNT

#include "../util/util.hpp"

namespace tifa_libs::bit {

// From GCC lib
template <typename T>
constexpr int popcnt(T x) {
  constexpr int nd = sizeof(T) * 8;
  constexpr int nd_ull = sizeof(unsigned long long) * 8;
  constexpr int nd_ul = sizeof(unsigned long) * 8;
  constexpr int nd_u = sizeof(unsigned) * 8;
  if constexpr (nd <= nd_u)
    return __builtin_popcount(x);
  else if constexpr (nd <= nd_ul)
    return __builtin_popcountl(x);
  else if constexpr (nd <= nd_ull)
    return __builtin_popcountll(x);
  else {
    static_assert(nd <= (2 * nd_ull), "Maximum supported integer size is 128-bit");
    unsigned long long lo = x & (unsigned long long)(-1), hi = x >> nd_ull;
    return __builtin_popcountll(lo) + __builtin_popcountll(hi);
  }
}

}  // namespace tifa_libs::bit

#endif