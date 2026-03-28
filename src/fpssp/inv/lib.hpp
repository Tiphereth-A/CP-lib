#pragma once

#include "../polysp/lib.hpp"

namespace tifa_libs {

template <poly_c poly_t>
CEXP auto inv_fpssp(poly_t CR p, u32 n = 0) NE {
  if (assert(!p.empty() && p[0] != 0); !n) n = (u32)p.size();
  auto ps = poly2sp(p, n);
  poly_t g(n);
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

}  // namespace tifa_libs
