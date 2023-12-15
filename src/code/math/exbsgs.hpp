#ifndef TIFALIBS_MATH_EXBSGS
#define TIFALIBS_MATH_EXBSGS

#include "bsgs.hpp"
#include "inverse.hpp"

namespace tifa_libs::math {

// solve a^x=b (mod m)
constexpr std::optional<u64> exbsgs(u64 a, u64 b, u64 m) {
  if (m == 0) return -1;
  a %= m;
  if ((b %= m) == 1 || m == 1) return 0;
  u64 cnt = 0, t = 1;
  for (u64 d = std::gcd(a, m); d != 1; d = std::gcd(a, m)) {
    if (b % d) return -1;
    ++cnt;
    b /= d;
    m /= d;
    (t *= a / d) %= m;
    if (b == t) return cnt;
  }
  auto ans = bsgs(a, b * inverse(t, m) % m, m);
  return ans ? ans.value() + cnt : ans;
}

}  // namespace tifa_libs::math

#endif