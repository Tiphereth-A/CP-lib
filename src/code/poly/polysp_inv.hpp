#ifndef TIFALIBS_POLY_POLYSP_INV
#define TIFALIBS_POLY_POLYSP_INV

#include "polysp.hpp"

namespace tifa_libs::math {

template <class poly>
constexpr poly polysp_inv(poly const& p, u32 n = 0) {
  assert(!p.data().empty() && p[0] != 0);
  if (!n) n = p.size();
  auto ps = poly2sp(p, n);
  poly g(n);
  auto _ = ps[0].second.inv();
  g[0] = _;
  for (u32 k = 1; k < n; k++) {
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