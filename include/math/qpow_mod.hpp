#ifndef TIFALIBS_MATH_QPOW_MOD
#define TIFALIBS_MATH_QPOW_MOD

#include "mul_mod.hpp"

namespace tifa_libs::math {

CEXP u64 qpow_mod(u64 a, u64 b, u64 mod) NE {
  u64 res(1);
  for (a %= mod; b; b >>= 1, a = mul_mod_u(a, a, mod)) {
    while (!(b & 1)) b >>= 1, a = mul_mod_u(a, a, mod);
    res = mul_mod_u(res, a, mod);
  }
  return res;
}

}  // namespace tifa_libs::math

#endif