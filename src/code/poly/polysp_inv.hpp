#ifndef TIFALIBS_POLYSP_INV
#define TIFALIBS_POLYSP_INV

#include "polysp.hpp"

namespace tifa_libs::math {

template <class T>
inline poly<T> polysp_inv(polysp<T> const& ps, size_t n) {
  assert(!ps.empty() && n && !ps[0].first && ps[0].second != 0);
  poly<T> g(n);
  auto _ = ps[0].second.inv();
  if (n) g[0] = _;
  for (size_t k = 1; k < n; k++) {
    for (auto& [j, fj] : ps) {
      if (k < j) break;
      g[k] += g[k - j] * fj;
    }
    g[k] *= -_;
  }
  return g;
}
template <class T>
inline poly<T> polysp_inv(poly<T> const& p, size_t n = 0) {
  assert(!p.data().empty() && p[0] != 0);
  if (!n) n = p.size();
  return polysp_inv<T>(poly2sp(p, n), n);
}

}  // namespace tifa_libs::math

#endif