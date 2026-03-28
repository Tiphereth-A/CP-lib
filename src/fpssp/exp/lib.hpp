#pragma once

#include "../../comb/seq/inv/lib.hpp"
#include "../polysp/lib.hpp"

namespace tifa_libs {

template <poly_c poly_t, class T, class... args>
CEXP auto exp_fpssp(poly_t CR p, vec<T> CR inv, u32 n = 0) NE {
  retif_((!p.size()) [[unlikely]], p);
  if (assert(p[0] == 0); !n) n = (u32)p.size();
  polysp<TPN poly_t::val_t> ps = poly2sp(p, n);
  poly_t g(n);
  g[0] = 1;
  flt_ (u32, k, 0, n - 1) {
    for (auto& [j, pj] : ps) {
      const u32 i = j - 1;
      if (k < i) break;
      g[k + 1] += pj * g[k - i] * j;
    }
    g[k + 1] *= inv[k + 1];
  }
  return g;
}
template <poly_c poly_t>
CEXP auto exp_fpssp(poly_t CR p, u32 n = 0) NE {
  if (!n) n = (u32)p.size();
  return exp_fpssp(p, gen_inv(n, poly_t::val_t::mod()), n);
}

}  // namespace tifa_libs
