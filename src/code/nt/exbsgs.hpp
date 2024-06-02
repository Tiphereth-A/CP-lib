#ifndef TIFALIBS_MATH_EXBSGS
#define TIFALIBS_MATH_EXBSGS

#include "bsgs.hpp"
#include "gcd.hpp"
#include "inverse.hpp"

namespace tifa_libs::math {

// solve a^x=b (mod m)
inline std::optional<u64> exbsgs(u64 a, u64 b, u64 m) {
  if (m == 0) return -1;
  if (a %= m; (b %= m) == 1 || m == 1) return 0;
  u64 cnt = 0, t = 1;
  for (u64 d = gcd(a, m); d != 1; d = gcd(a, m)) {
    if (b % d) return -1;
    if (++cnt, b /= d, m /= d, (t *= a / d) %= m; b == t) return cnt;
  }
  auto ans = bsgs(a, b * inverse(t, m) % m, m);
  return ans ? ans.value() + cnt : ans;
}

}  // namespace tifa_libs::math

#endif