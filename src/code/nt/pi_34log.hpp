#ifndef TIFALIBS_MATH_PI_34LOG
#define TIFALIBS_MATH_PI_34LOG

#include "../math/div64.hpp"
#include "../math/isqrt.hpp"

namespace tifa_libs::math {

CEXP u64 pi_34log(u64 n) {
  if (n < 2) return 0;
  u64 n2 = isqrt(n), ndn2 = div_u64d(n, n2);
  vecu64 hl(ndn2);
  flt_ (u32, i, 1, ndn2) hl[i] = div_u64d(n, i) - 1;
  vecu hs(n2 + 1);
  std::iota(hs.begin(), hs.end(), -1_u32);
  for (u64 x = 2, pi = 0; x <= n2; ++x) {
    if (hs[x] == hs[x - 1]) continue;
    u64 x2 = x * x, mx = min(ndn2, div_u64d(n, x2) + 1), ix = x;
    flt_ (u64, i, 1, mx) {
      hl[i] -= (ix < ndn2 ? hl[ix] : hs[div_u64d(n, ix)]) - pi;
      ix += x;
    }
    for (u64 n = n2; n >= x2; --n) hs[n] -= hs[div_u64d(n, x)] - pi;
    ++pi;
  }
  return hl[1];
}

}  // namespace tifa_libs::math

#endif