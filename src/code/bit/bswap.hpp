#ifndef TIFA_LIBS_BIT_BSWAP
#define TIFA_LIBS_BIT_BSWAP

namespace tifa_libs::bit {

// From GCC lib
template <typename T>
constexpr T bswap(T x) {
  if constexpr (sizeof(T) == 2) return __builtin_bswap16(x);
  if constexpr (sizeof(T) == 4) return __builtin_bswap32(x);
  if constexpr (sizeof(T) == 8) return __builtin_bswap64(x);
  if constexpr (sizeof(T) == 16) return (__builtin_bswap64(x >> 64) | (static_cast<T>(__builtin_bswap64(x)) << 64));
}

}  // namespace tifa_libs::bit

#endif