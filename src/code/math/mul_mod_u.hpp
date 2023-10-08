#ifndef TIFA_LIBS_MATH_MUL_MOD_U
#define TIFA_LIBS_MATH_MUL_MOD_U

#include "../bit/bwidth.hpp"
#include "../util/util.hpp"

namespace tifa_libs::math {

constexpr u64 mul_mod_u(u64 a, u64 b, u64 mod) {
  if (bit::bwidth(a) + bit::bwidth(b) <= 64) return a * b % mod;
  else return (u64)((u128)a * b % mod);
}

}  // namespace tifa_libs::math

#endif