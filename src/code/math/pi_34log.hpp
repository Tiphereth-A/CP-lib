#ifndef TIFA_LIBS_MATH_PI_34LOG
#define TIFA_LIBS_MATH_PI_34LOG

#include "isqrt.hpp"

namespace tifa_libs::math {

inline u64 pi_34log(u64 n) {
  if (n < 2) return 0;
  static auto div = [](u64 n, u64 p) -> u64 { return (u64)((double)n / (double)p); };
  u64 n2 = isqrt(n), ndn2 = div(n, n2);
  vec<u64> hl(ndn2);
  for (usz i = 1; i < ndn2; ++i) hl[i] = div(n, i) - 1;
  vec<u32> hs(n2 + 1);
  std::iota(hs.begin(), hs.end(), (u32)-1);
  for (u64 x = 2, pi = 0; x <= n2; ++x) {
    if (hs[x] == hs[x - 1]) continue;
    u64 x2 = x * x, mx = std::min(ndn2, div(n, x2) + 1), ix = x;
    for (u64 i = 1; i < mx; ++i) {
      hl[i] -= (ix < ndn2 ? hl[ix] : hs[div(n, ix)]) - pi;
      ix += x;
    }
    for (u64 n = n2; n >= x2; --n) hs[n] -= hs[div(n, x)] - pi;
    ++pi;
  }
  return hl[1];
}

}  // namespace tifa_libs::math

#endif