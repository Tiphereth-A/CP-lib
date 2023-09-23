#ifndef TIFA_LIBS_MATH_BSGS
#define TIFA_LIBS_MATH_BSGS

#include "../util/util.hpp"

#include "isqrt.hpp"
#include "qpow_mod.hpp"

namespace tifa_libs::math {

// solve a^x=b (mod m)
//! gcd(a, m) == 1 required
inline std::optional<u64> bsgs(u64 a, u64 b, u64 m) {
  a %= m;
  std::map<u64, u64> hmp;
  u64 sqrt_m = isqrt(m), s = mul_mod_u(a, b, m);
  if (sqrt_m * sqrt_m < m) ++sqrt_m;
  for (u64 i = 1; i <= sqrt_m; ++i, s = mul_mod_u(s, a, m)) hmp[s] = i;
  u64 _ = qpow_mod(a, sqrt_m, m);
  s = _;
  for (u64 i = 1; i <= sqrt_m; ++i, s = mul_mod_u(s, _, m))
    if (hmp[s] && i * sqrt_m >= hmp[s]) return (i64)(i * sqrt_m - hmp[s]);
  return {};
}

}  // namespace tifa_libs::math

#endif