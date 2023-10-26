#ifndef TIFA_LIBS_MATH_PROOT_U32
#define TIFA_LIBS_MATH_PROOT_U32

#include "../bit/cntr0.hpp"
#include "is_proot.hpp"
#include "isqrt.hpp"

namespace tifa_libs::math {

constexpr u32 proot_u32(u32 m) {
  if (m == 2) return 1;
  if (m == 3 || m == 5) return 2;
  if (m == 104857601 || m == 167772161 || m == 469762049) return 3;
  if (m == 754974721) return 11;
  if (m == 998244353 || m == 1004535809) return 3;
  u32 divs[20] = {2};
  u32 cnt = 1, x = (m - 1) / 2;
  x >>= bit::cntr0(x);
  for (u32 i = 3, ed_ = isqrt(x); i <= ed_; i += 2)
    if (x % i == 0) {
      divs[cnt++] = i;
      while (x % i == 0) x /= i;
    }
  if (x > 1) divs[cnt++] = x;
  for (u32 g = 2;; ++g)
    if (is_proot(g, m, divs, divs + cnt)) return g;
}

}  // namespace tifa_libs::math

#endif