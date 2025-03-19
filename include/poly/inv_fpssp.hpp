#ifndef TIFALIBS_POLY_INV_FPSSP
#define TIFALIBS_POLY_INV_FPSSP

#include "polysp.hpp"

namespace tifa_libs::math {

template <template <class... Ts> class ccore, class mint, class... args>
CEXP auto inv_fpssp(poly<ccore, mint, args...> CR p, u32 n = 0) NE {
  if (assert(!p.empty() && p[0] != 0); !n) n = (u32)p.size();
  auto ps = poly2sp(p, n);
  poly<ccore, mint, args...> g(n);
  auto _ = ps[0].second.inv();
  g[0] = _;
  flt_ (u32, k, 1, n) {
    for (auto& [j, fj] : ps) {
      if (k < j) break;
      g[k] += g[k - j] * fj;
    }
    g[k] *= -_;
  }
  return g;
}

}  // namespace tifa_libs::math

#endif