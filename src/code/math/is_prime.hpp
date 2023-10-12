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
  auto f = [d = (n - 1) >> bit::cntr0(n - 1), n](u64 i) {
    u64 t = d, y = qpow_mod(i, t, n);
    while (t != n - 1 && y != 1 && y != n - 1) {
      y = mul_mod_u(y, y, n);
      t <<= 1;
    }
    return !(y != n - 1 && (~t & 1));
  };
  if (n <= (u32)-1) {
    for (auto i : {2, 7, 61})
      if (!f((u64)i)) return false;
  } else
    for (auto i : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
      if (n < (u64)i) return true;
      if (!f((u64)i)) return false;
    }
  return true;
}

}  // namespace tifa_libs::math

#endif