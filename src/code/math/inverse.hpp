#ifndef TIFALIBS_MATH_INVERSE
#define TIFALIBS_MATH_INVERSE

#include "inv_gcd.hpp"

namespace tifa_libs::math {

constexpr u64 inverse(u64 n, u64 mod) {
  auto [g, x] = inv_gcd(n % mod, mod);
  assert(g == 1);
  return x;
}

}  // namespace tifa_libs::math

#endif