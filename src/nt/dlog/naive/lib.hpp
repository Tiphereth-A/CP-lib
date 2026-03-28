#pragma once

#include "../../../math/mul_mod/lib.hpp"

namespace tifa_libs {

inline auto dlog_naive(u64 a, u64 b, u64 m) NE {
  std::optional<u64> ret;
  retif_((m == 0) [[unlikely]], ret);
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
  flt_ (u32, i, 0, (u32)m, pow_a = 1) {
    if (pow_a == b) {
      ret.emplace(i);
      return ret;
    }
    pow_a = (u32)mul_mod_u(pow_a, a, m);
  }
  return ret;
}

}  // namespace tifa_libs
