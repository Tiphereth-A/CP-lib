#ifndef TIFALIBS_POLY_POLYSP_LN
#define TIFALIBS_POLY_POLYSP_LN

#include "../comb/gen_inv.hpp"
#include "polysp.hpp"

namespace tifa_libs::math {

template <class T>
poly<T> polysp_ln(poly<T> const& p, vec<u64> const& inv, u32 n = 0) {
  assert(!p.data().empty() && p[0] == 1);
  if (!n) n = p.size();
  polysp<T> ps = poly2sp(p, n);
  poly<T> g(n);
  for (u32 k = 0; k < n - 1; ++k) {
    for (auto& [j, pj] : ps) {
      if (k < j) break;
      u32 i = k - j + 1;
      g[k + 1] -= g[i] * pj * i;
    }
    g[k + 1] *= inv[k + 1];
    if (k + 1 < p.size()) g[k + 1] += p[k + 1];
  }
  return g;
}
template <class T>
poly<T> polysp_ln(poly<T> const& p, u32 n = 0) {
  if (!n) n = p.size();
  return polysp_ln(p, gen_inv(n, T::value_type::mod()), n);
}

}  // namespace tifa_libs::math

#endif