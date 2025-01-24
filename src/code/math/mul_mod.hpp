#ifndef TIFALIBS_MATH_MUL_MOD
#define TIFALIBS_MATH_MUL_MOD

#include "safe_mod.hpp"

namespace tifa_libs::math {

CEXP i64 mul_mod_s(i64 a, i64 b, u64 mod) NE {
  if (std::bit_width((u64)abs(a)) + std::bit_width((u64)abs(b)) < 64) return safe_mod(a * b % (i64)mod, mod);
  return safe_mod((i64)((i128)a * b % mod), mod);
}
CEXP u64 mul_mod_u(u64 a, u64 b, u64 mod) NE {
  if (std::bit_width(a) + std::bit_width(b) <= 64) return a * b % mod;
  return (u64)((u128)a * b % mod);
}

}  // namespace tifa_libs::math

#endif