#ifndef TIFALIBS_MATH_BSGS
#define TIFALIBS_MATH_BSGS

#include "../math/barrett.hpp"
#include "../math/isqrt.hpp"
#include "../math/qpow_mod.hpp"
#include "../util/alias_others.hpp"

namespace tifa_libs::math {

// solve $a^x\equiv b \pmod m$
//! $\gcd(a, m) = 1$ required
inline auto bsgs(u64 a, u64 b, u64 m) NE {
  a %= m, b %= m;
  std::optional<u64> ret;
  hmap<u64, u64> hmp;
  barrett<0> brt(m, a);
  u64 sqrt_m = isqrt(m), s = brt.reduce(b);
  if (sqrt_m * sqrt_m < m) ++sqrt_m;
  for (u64 i = 1; i <= sqrt_m; ++i, s = brt.reduce(s)) hmp[s] = i;
  const u64 _ = qpow_mod(a, sqrt_m, m);
  s = _, brt.reset(m, _);
  for (u64 i = 1; i <= sqrt_m; ++i, s = brt.reduce(s))
    if (hmp[s] && i * sqrt_m >= hmp[s]) {
      ret.emplace(i * sqrt_m - hmp[s]);
      return ret;
    }
  return ret;
}

}  // namespace tifa_libs::math

#endif