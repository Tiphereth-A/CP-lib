#ifndef TIFALIBS_MATH_MUL_MOD_U
#define TIFALIBS_MATH_MUL_MOD_U

#include "../util/util.hpp"

namespace tifa_libs::math {

CEXP u64 mul_mod_u(u64 a, u64 b, u64 mod) {
  if (std::bit_width(a) + std::bit_width(b) <= 64) return a * b % mod;
  return (u64)((u128)a * b % mod);
}

}  // namespace tifa_libs::math

#endif