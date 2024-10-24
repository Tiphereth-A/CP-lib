#ifndef TIFALIBS_POLY_EXP_FPSSP
#define TIFALIBS_POLY_EXP_FPSSP

#include "../comb/gen_inv.hpp"
#include "polysp.hpp"

namespace tifa_libs::math {

template <class mint, class ccore>
CEXP poly<mint, ccore> exp_fpssp(poly<mint, ccore> CR p, spnuu inv, u32 n = 0) {
  if (p.data().empty()) return p;
  assert(p[0] == 0);
  if (!n) n = p.size();
  polysp<mint> ps = poly2sp(p, n);
  poly<mint, ccore> g(n);
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
template <class mint, class ccore>
CEXP poly<mint, ccore> exp_fpssp(poly<mint, ccore> CR p, u32 n = 0) {
  if (!n) n = p.size();
  return exp_fpssp(p, gen_inv(n, mint::mod()), n);
}

}  // namespace tifa_libs::math

#endif