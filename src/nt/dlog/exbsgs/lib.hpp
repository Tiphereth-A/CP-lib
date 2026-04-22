#pragma once

#include "../../gl/gcd/lib.hpp"
#include "../../inverse/lib.hpp"
#include "../naive/lib.hpp"

namespace tifa_libs {

// solve $a^x\equiv b \pmod m$
inline auto exbsgs(auto&& bsgs, u64 a, u64 b, u64 m) NE {
  std::optional<u64> ret;
  if (m < 64) {
    ret = dlog_naive(a, b, m);
    return ret;
  }
  if (a %= m, b %= m; b == 1) {
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
  u64 cnt = 0, t = 1;
  for (u64 d = gcd(a, m); d != 1; d = gcd(a, m)) {
    if (b % d) return ret;
    if (++cnt, b /= d, m /= d, (t *= a / d) %= m; b == t) {
      ret.emplace(cnt);
      return ret;
    }
  }
  if (ret = bsgs(a, b * inverse(t, m), m); ret) ret.value() += cnt;
  return ret;
}

}  // namespace tifa_libs
