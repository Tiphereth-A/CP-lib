#ifndef TIFALIBS_BIT_FFS
#define TIFALIBS_BIT_FFS

#include "../util/util.hpp"

namespace tifa_libs::bit {

template <class T>
CEXP int ffs(T x) NE {
  CEXP int nd = sizeof(T) * 8;
  static_assert(nd <= 128);
  CEXP int nd_ull = sizeof(long long) * 8;
  if CEXP (nd <= sizeof(int) * 8) return __builtin_ffs(x);
  else if CEXP (nd <= sizeof(long) * 8) return __builtin_ffsl(x);
  else if CEXP (nd <= nd_ull) return __builtin_ffsll(x);
  else {
    retif_((!x) [[unlikely]], 0);
    if (const long long lo = x & (long long)(-1); lo) return __builtin_ffsll(lo);
    return __builtin_ffsll(x >> nd_ull) + 64;
  }
}

}  // namespace tifa_libs::bit

#endif