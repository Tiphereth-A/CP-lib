#ifndef TIFALIBS_BIT_BSWAP
#define TIFALIBS_BIT_BSWAP

#include "../util/util.hpp"

namespace tifa_libs::bit {

// From GCC lib
template <class T>
CEXP T bswap(T x) NE {
  if CEXP (sizeof(T) == 2) return __builtin_bswap16(x);
  if CEXP (sizeof(T) == 4) return __builtin_bswap32(x);
  if CEXP (sizeof(T) == 8) return __builtin_bswap64(x);
  if CEXP (sizeof(T) == 16) return __builtin_bswap128(x);
  // if CEXP (sizeof(T) == 16) return (__builtin_bswap64(x >> 64) | (static_cast<T>(__builtin_bswap64(x)) << 64));
}

}  // namespace tifa_libs::bit

#endif