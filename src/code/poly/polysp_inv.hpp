#ifndef TIFALIBS_POLYSP_INV
#define TIFALIBS_POLYSP_INV

#include "polysp.hpp"

namespace tifa_libs::math {

template <class T>
inline poly<T> polysp_inv(poly<T> const& p, usz n = 0) {
  assert(!p.data().empty() && p[0] != 0);
  if (!n) n = p.size();
  polysp<T> ps = poly2sp(p, n);
  poly<T> g(n);
  auto _ = ps[0].second.inv();
  g[0] = _;
  for (usz k = 1; k < n; k++) {
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