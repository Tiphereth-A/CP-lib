#ifndef TIFA_LIBS_BIT_PARITY
#define TIFA_LIBS_BIT_PARITY

namespace tifa_libs::bit {

template <class T>
constexpr int parity(T x) {
  constexpr int nd = sizeof(T) * 8;
  static_assert(nd <= 128);
  constexpr int nd_ull = sizeof(unsigned long long) * 8;
  if constexpr (nd <= sizeof(unsigned) * 8) return __builtin_parity(x);
  else if constexpr (nd <= sizeof(unsigned long) * 8) return __builtin_parityl(x);
  else if constexpr (nd <= nd_ull) return __builtin_parityll(x);
  else {
    unsigned long long lo = x & (unsigned long long)(-1), hi = x >> nd_ull;
    return __builtin_parityll(hi) ^ __builtin_parityll(lo);
  }
}

}  // namespace tifa_libs::bit

#endif