#ifndef TIFALIBS_POLY_INV_FPSSP
#define TIFALIBS_POLY_INV_FPSSP

#include "polysp.hpp"

namespace tifa_libs::math {

template <class mint, class ccore>
CEXP poly<mint, ccore> inv_fpssp(poly<mint, ccore> CR p, u32 n = 0) {
  assert(!p.data().empty() && p[0] != 0);
  if (!n) n = p.size();
  auto ps = poly2sp(p, n);
  poly<mint, ccore> g(n);
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