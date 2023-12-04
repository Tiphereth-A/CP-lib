#ifndef TIFALIBS_MATH_INV_GCD
#define TIFALIBS_MATH_INV_GCD

#include "exgcd.hpp"
#include "safe_mod.hpp"

namespace tifa_libs::math {

constexpr std::pair<u64, u64> inv_gcd(u64 n, u64 mod) {
  auto [g, x, y] = exgcd((i64)(n % mod), (i64)mod);
  return {g, safe_mod(x, mod)};
}

}  // namespace tifa_libs::math

#endif