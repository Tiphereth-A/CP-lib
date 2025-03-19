#ifndef TIFALIBS_POLY_EXP_FPSSP
#define TIFALIBS_POLY_EXP_FPSSP

#include "../comb/gen_inv.hpp"
#include "polysp.hpp"

namespace tifa_libs::math {

template <template <class... Ts> class ccore, class mint, class T, class... args>
CEXP auto exp_fpssp(poly<ccore, mint, args...> CR p, vec<T> CR inv, u32 n = 0) NE {
  if (!p.size()) return p;
  if (assert(p[0] == 0); !n) n = (u32)p.size();
  polysp<mint> ps = poly2sp(p, n);
  poly<ccore, mint, args...> g(n);
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
template <template <class... Ts> class ccore, class mint, class... args>
CEXP auto exp_fpssp(poly<ccore, mint, args...> CR p, u32 n = 0) NE {
  if (!n) n = (u32)p.size();
  return exp_fpssp(p, gen_inv(n, mint::mod()), n);
}

}  // namespace tifa_libs::math

#endif