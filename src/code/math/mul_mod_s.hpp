#ifndef TIFA_LIBS_MATH_MUL_MOD_S
#define TIFA_LIBS_MATH_MUL_MOD_S

#include "../bit/bwidth.hpp"
#include "../util/abs_constexpr.hpp"
#include "safe_mod.hpp"

namespace tifa_libs::math {

constexpr u64 mul_mod_s(i64 a, i64 b, u64 mod) {
  if (bit::bwidth((u64)abs(a)) + bit::bwidth((u64)abs(b)) < 64) return (u64)safe_mod(a * b % (i64)mod, mod);
  else return (u64)safe_mod((i64)((i128)a * b % mod), mod);
}

}  // namespace tifa_libs::math

#endif