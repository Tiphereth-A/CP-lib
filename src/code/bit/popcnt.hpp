#ifndef TIFALIBS_BIT_POPCNT
#define TIFALIBS_BIT_POPCNT

namespace tifa_libs::bit {

// From GCC lib
template <class T>
constexpr int popcnt(T x) {
  constexpr int nd = sizeof(T) * 8;
  static_assert(nd <= 128);
  constexpr int nd_ull = sizeof(unsigned long long) * 8;
  if constexpr (nd <= sizeof(unsigned) * 8) return __builtin_popcount(x);
  else if constexpr (nd <= sizeof(unsigned long) * 8) return __builtin_popcountl(x);
  else if constexpr (nd <= nd_ull) return __builtin_popcountll(x);
  else {
    unsigned long long lo = x & (unsigned long long)(-1), hi = x >> nd_ull;
    return __builtin_popcountll(lo) + __builtin_popcountll(hi);
  }
}

}  // namespace tifa_libs::bit

#endif