#ifndef TIFALIBS_MATH_BSGS
#define TIFALIBS_MATH_BSGS

#include "../math/isqrt.hpp"
#include "../math/qpow_mod.hpp"
#include "../util/alias_others.hpp"
#include "barrett.hpp"
#include "dlog_naive.hpp"

namespace tifa_libs::math {

// solve $a^x\equiv b \pmod m$
inline auto bsgs(u64 a, u64 b, u64 m) NE {
  std::optional<u64> ret;
  if (m < 64) {
    ret = dlog_naive(a, b, m);
    return ret;
  }
  if (a %= m, b %= m; m == 1 || b == 1) {
    ret.emplace(0);
    return ret;
  }
  if (!a) {
    if (!b) ret.emplace(1);
    return ret;
  }
  if (a == 1) {
    if (b == 1) ret.emplace(0);
    return ret;
  }
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