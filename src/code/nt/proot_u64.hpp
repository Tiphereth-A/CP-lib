#ifndef TIFALIBS_MATH_PROOT_U64
#define TIFALIBS_MATH_PROOT_U64

#include "pfactors.hpp"
#include "proot_u32.hpp"

namespace tifa_libs::math {

inline u64 proot(u64 m) {
  if (m <= (u64)-1_u32) return proot((u32)m);
  vecu64 pf;
  {
    auto _ = pfactors(m - 1);
    pf.reserve(_.size());
    for (auto [k, v] : _) pf.push_back(k);
  }
  u64 g = 2;
  for (;; ++g)
    if (is_proot(g, m, pf.begin(), pf.end())) break;
  return g;
}

}  // namespace tifa_libs::math

#endif