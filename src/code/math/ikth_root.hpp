#ifndef TIFALIBS_MATH_IKTH_ROOT
#define TIFALIBS_MATH_IKTH_ROOT

#include "../util/util.hpp"

namespace tifa_libs::math {

constexpr u64 ikth_root(u64 a, u64 k) {
  assert(k);
  if (a <= 1 || k == 1) return a;
  if (k >= 64) return 1;
  auto chk = [&](u128 n) {
    u128 x = 1, m = n;
    for (u64 p = k; p; p /= 2, m *= m)
      if (p & 1) x *= m;
    return x <= a;
  };
  u64 n = (u64)powl(a, 1.l / k);
  while (!chk(n)) --n;
  while (chk(n + 1)) ++n;
  return n;
}

}  // namespace tifa_libs::math

#endif