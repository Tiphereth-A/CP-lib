#ifndef TIFALIBS_MATH_PERIOD_FIB
#define TIFALIBS_MATH_PERIOD_FIB

#include "../math/isqrt.hpp"
#include "lcm.hpp"

namespace tifa_libs::math {

//! Not the minimal
CEXP u64 period_fib(u32 n) NE {
  auto g = [](u64 p) NE -> u64 {
    static CEXP u32 _[6] = {0, 1, 3, 8, 6, 20};
    if (p <= 5) return _[p];
    return (p % 5 == 1 || p % 5 == 4) ? (p - 1) : ((p + 1) * 2);
  };

  u64 res = 1;
  flt_ (u32, i, 2, isqrt(n) + 1)
    if (n % i == 0) {
      n /= i;
      u64 x = g(i), _ = n;
      while (n % i == 0) n /= i;
      x *= _ / n, res = lcm(res, x);
    }
  if (n > 1) res = lcm(res, g(n));
  return res;
}

}  // namespace tifa_libs::math

#endif