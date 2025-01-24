#ifndef TIFALIBS_MATH_IKTH_ROOT
#define TIFALIBS_MATH_IKTH_ROOT

#include "qpow.hpp"

namespace tifa_libs::math {

CEXP u64 ikth_root(u64 a, u64 k) NE {
  if (assert(k); a <= 1 || k == 1) return a;
  if (k >= 64) return 1;
  u64 n = (u64)powl(a, 1.l / k);
  while (qpow<u128>(n, k) > a) --n;
  while (qpow<u128>(n + 1, k) <= a) ++n;
  return n;
}

}  // namespace tifa_libs::math

#endif