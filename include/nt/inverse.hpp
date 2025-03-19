#ifndef TIFALIBS_MATH_INVERSE
#define TIFALIBS_MATH_INVERSE

#include "inv_gcd.hpp"

namespace tifa_libs::math {

template <uint_c T, uint_c U>
CEXP U inverse(T n, U mod) NE {
  auto [g, x] = inv_gcd(U(n % mod), mod);
  assert(g == 1);
  return x;
}

}  // namespace tifa_libs::math

#endif