#ifndef TIFALIBS_POLYSP_POW
#define TIFALIBS_POLYSP_POW

#include "../comb/inv_mod_gen.hpp"
#include "../math/qpow.hpp"
#include "poly_shl.hpp"
#include "poly_shr.hpp"
#include "polysp.hpp"

namespace tifa_libs::math {

template <class T>
inline poly<T> polysp_pow(poly<T> const& p, u64 y, vec<u64> const& inv, usz n = 0) {
  if (!n) n = p.size();
  if (!y) return poly<T>{1}.pre(n);
  if (p.data().empty()) return p.pre(n);
  usz l0 = std::find_if(p.data().begin(), p.data().end(), [](auto const& x) { return x != 0; }) - p.data().begin();
  if ((u128)l0 * y >= n) return poly<T>(n);
  if (l0) {
    auto _ = poly_shr(p, l0), g = polysp_pow(_, y, inv, n - l0 * y);
    g.resize(n);
    return poly_shl(g, l0 * y);
  }
  polysp<T> ps = poly2sp(p, n);
  poly<T> g(n);
  g[0] = qpow(p[0], y);
  auto _ = p[0].inv();
  for (u64 k = 1, y_ = y % T::value_type::mod(); k < n; ++k) {
    for (auto& [j, pj] : ps) {
      if (k < j) break;
      g[k] += pj * g[k - j] * ((y_ + 1) * j - k);
    }
    g[k] *= _ * inv[k];
  }
  return g;
}
template <class T>
inline poly<T> polysp_pow(poly<T> const& p, u64 y, usz n = 0) {
  if (!n) n = p.size();
  return polysp_pow(p, y, inv_mod_gen(n, T::value_type::mod()), n);
}

}  // namespace tifa_libs::math

#endif