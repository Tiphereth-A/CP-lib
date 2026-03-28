#pragma once

#include "../../comb/seq/inv/lib.hpp"
#include "../polysp/lib.hpp"

namespace tifa_libs {

template <poly_c poly_t, class T>
CEXP auto ln_fpssp(poly_t CR p, vec<T> CR inv, u32 n = 0) NE {
  if (assert(!p.empty() && p[0] == 1); !n) n = (u32)p.size();
  auto ps = poly2sp(p, n);
  poly_t g(n);
  flt_ (u32, k, 0, n - 1) {
    for (auto& [j, pj] : ps) {
      if (k < j) break;
      const u32 i = k - j + 1;
      g[k + 1] -= g[i] * pj * i;
    }
    if (g[k + 1] *= inv[k + 1]; k + 1 < p.size()) g[k + 1] += p[k + 1];
  }
  return g;
}
template <poly_c poly_t>
CEXP auto ln_fpssp(poly_t CR p, u32 n = 0) NE {
  if (!n) n = (u32)p.size();
  return ln_fpssp(p, gen_inv(n, poly_t::val_t::mod()), n);
}

}  // namespace tifa_libs
