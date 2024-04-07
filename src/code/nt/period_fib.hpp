#ifndef TIFALIBS_MATH_PERIOD_FIB
#define TIFALIBS_MATH_PERIOD_FIB

#include "../util/util.hpp"

namespace tifa_libs::math {

//! Not the minimal
constexpr u64 period_fib(u32 n) {
  auto g = [](u64 p) -> u64 {
    static constexpr u32 _[6] = {0, 1, 3, 8, 6, 20};
    if (p <= 5) return _[p];
    return (p % 5 == 1 || p % 5 == 4) ? (p - 1) : ((p + 1) * 2);
  };

  u64 res = 1;
  for (u32 i = 2; (u64)i * i <= n; ++i)
    if (n % i == 0) {
      n /= i;
      u64 x = g(i), _ = n;
      while (n % i == 0) n /= i;
      x *= _ / n, res = res / std::gcd(res, x) * x;
    }
  if (n > 1) {
    u64 x = g(n);
    res = res / std::gcd(res, x) * x;
  }
  return res;
}

}  // namespace tifa_libs::math

#endif