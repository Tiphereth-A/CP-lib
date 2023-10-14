#ifndef TIFALIBS_POLYSP_EXP
#define TIFALIBS_POLYSP_EXP

#include "../comb/inv_mod_gen.hpp"
#include "polysp.hpp"

namespace tifa_libs::math {

template <class T>
inline poly<T> polysp_exp(poly<T> const& p, vec<u64> const& inv, size_t n = 0) {
  if (p.data().empty()) return p;
  assert(p[0] == 0);
  if (!n) n = p.size();
  polysp<T> ps = poly2sp(p, n);
  poly<T> g(n);
  g[0] = 1;
  for (size_t k = 0; k < n - 1; ++k) {
    for (auto& [j, pj] : ps) {
      size_t i = j - 1;
      if (k < i) break;
      g[k + 1] += pj * g[k - i] * j;
    }
    g[k + 1] *= inv[k + 1];
  }
  return g;
}
template <class T>
inline poly<T> polysp_exp(poly<T> const& p, size_t n = 0) {
  if (!n) n = p.size();
  return polysp_exp(p, inv_mod_gen(n, T::value_type::mod()), n);
}

}  // namespace tifa_libs::math

#endif