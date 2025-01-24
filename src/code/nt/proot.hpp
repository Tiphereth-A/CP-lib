#ifndef TIFALIBS_MATH_PROOT
#define TIFALIBS_MATH_PROOT

#include "is_proot.hpp"
#include "pfactors.hpp"

namespace tifa_libs::math {

CEXP u64 proot(u64 m) NE {
  if (m == 2) return 1;
  if (m == 3 || m == 5) return 2;
  if (m == 104857601 || m == 167772161 || m == 469762049 || m == 998244353 || m == 1004535809) return 3;
  if (m == 1012924417) return 5;
  if (m == 754974721) return 11;
  const auto pf = pfactors(m - 1);
  for (u64 g = 2;; ++g)
    if (is_proot(g, m, pf.begin(), pf.end())) return g;
}

}  // namespace tifa_libs::math

#endif