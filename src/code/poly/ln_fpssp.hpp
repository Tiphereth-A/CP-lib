#ifndef TIFALIBS_POLY_LN_FPSSP
#define TIFALIBS_POLY_LN_FPSSP

#include "../comb/gen_inv.hpp"
#include "polysp.hpp"

namespace tifa_libs::math {

template <class mint, class ccore>
CEXP poly<mint, ccore> ln_fpssp(poly<mint, ccore> CR p, vecu64 CR inv, u32 n = 0) {
  assert(!p.data().empty() && p[0] == 1);
  if (!n) n = p.size();
  auto ps = poly2sp(p, n);
  poly<mint, ccore> g(n);
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
template <class mint, class ccore>
CEXP poly<mint, ccore> ln_fpssp(poly<mint, ccore> CR p, u32 n = 0) {
  if (!n) n = p.size();
  return ln_fpssp(p, gen_inv(n, mint::mod()), n);
}

}  // namespace tifa_libs::math

#endif