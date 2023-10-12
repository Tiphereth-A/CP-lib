#ifndef TIFA_LIBS_MATH_IS_PRIME
#define TIFA_LIBS_MATH_IS_PRIME

#include "../bit/cntr0.hpp"
#include "mul_mod_u.hpp"
#include "qpow_mod.hpp"

namespace tifa_libs::math {

constexpr bool is_prime(u64 n) {
  if (n <= 2) return n == 2;
  if (~n & 1) return false;
  if (n < 8) return true;
  constexpr u64 bases[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
  u64 d = (n - 1) >> bit::cntr0(n - 1);
  for (u64 i : bases) {
    if (n == i) return true;
    u64 t = d, y = qpow_mod(i, t, n);
    while (t != n - 1 && y != 1 && y != n - 1) {
      y = mul_mod_u(y, y, n);
      t <<= 1;
    }
    if (y != n - 1 && (~t & 1)) return false;
  }
  return true;
}

}  // namespace tifa_libs::math

#endif