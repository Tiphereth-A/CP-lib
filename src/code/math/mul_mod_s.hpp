#ifndef TIFALIBS_MATH_MUL_MOD_S
#define TIFALIBS_MATH_MUL_MOD_S

#include "safe_mod.hpp"

namespace tifa_libs::math {

constexpr i64 mul_mod_s(i64 a, i64 b, u64 mod) {
  if (std::bit_width((u64)abs(a)) + std::bit_width((u64)abs(b)) < 64) return safe_mod(a * b % (i64)mod, mod);
  else return safe_mod((i64)((i128)a * b % mod), mod);
}

}  // namespace tifa_libs::math

#endif