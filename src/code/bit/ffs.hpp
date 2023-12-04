#ifndef TIFALIBS_BIT_FFS
#define TIFALIBS_BIT_FFS

namespace tifa_libs::bit {

template <class T>
constexpr int ffs(T x) {
  constexpr int nd = sizeof(T) * 8;
  static_assert(nd <= 128);
  constexpr int nd_ull = sizeof(long long) * 8;
  if constexpr (nd <= sizeof(int) * 8) return __builtin_ffs(x);
  else if constexpr (nd <= sizeof(long) * 8) return __builtin_ffsl(x);
  else if constexpr (nd <= nd_ull) return __builtin_ffsll(x);
  else {
    if (!x) return 0;
    long long lo = x & (long long)(-1);
    if (lo) return __builtin_ffsll(lo);
    long long hi = x >> nd_ull;
    return __builtin_ffsll(hi) + 64;
  }
}

}  // namespace tifa_libs::bit

#endif