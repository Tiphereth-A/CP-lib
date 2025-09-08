#ifndef TIFALIBS_MATH_EXBSGS
#define TIFALIBS_MATH_EXBSGS

#include "bsgs.hpp"
#include "gcd.hpp"
#include "inverse.hpp"

namespace tifa_libs::math {

// solve $a^x\equiv b \pmod m$
inline auto exbsgs(u64 a, u64 b, u64 m) NE {
  std::optional<u64> ret;
  retif_((m == 0) [[unlikely]], ret);
  if (a %= m; (b %= m) == 1 || m == 1) {
    ret.emplace(0);
    return ret;
  }
  u64 cnt = 0, t = 1;
  for (u64 d = gcd(a, m); d != 1; d = gcd(a, m)) {
    if (b % d) return ret;
    if (++cnt, b /= d, m /= d, (t *= a / d) %= m; b == t) {
      ret.emplace(cnt);
      return ret;
    }
  }
  if (ret = bsgs(a, b * inverse(t, m) % m, m); ret) ret.value() += cnt;
  return ret;
}

}  // namespace tifa_libs::math

#endif