#ifndef TIFALIBS_POLY_POW_FPSSP
#define TIFALIBS_POLY_POW_FPSSP

#include "../comb/gen_inv.hpp"
#include "../math/qpow.hpp"
#include "polysp.hpp"
#include "shl_fps.hpp"
#include "shr_fps.hpp"

namespace tifa_libs::math {

template <template <class... Ts> class ccore, class mint, class T, class... args>
CEXP auto pow_fpssp(poly<ccore, mint, args...> CR p, u64 y, vec<T> CR inv, u32 n = 0) NE {
  if (!n) n = (u32)p.size();
  if (!y) return poly<ccore, mint, args...>{1}.pre(n);
  if (p.is_zero()) return p.pre(n);
  const u32 l0 = u32(std::ranges::find_if(p, [](cT_(mint) x) NE { return x.val() != 0; }) - p.begin());
  if ((u128)l0 * y >= n) return poly<ccore, mint, args...>(n);
  if (l0) {
    auto _ = shr_fps(p, l0), g = pow_fpssp(_, y, inv, u32(n - l0 * y));
    g.resize(n);
    return shl_fps(g, l0 * y);
  }
  auto ps = poly2sp(p, n);
  poly<ccore, mint, args...> g(n);
  g[0] = qpow(p[0], y);
  auto _ = p[0].inv();
  for (u64 k = 1, y_ = y % mint::mod(); k < n; ++k) {
    for (auto& [j, pj] : ps) {
      if (k < j) break;
      g[(u32)k] += pj * g[u32(k - j)] * ((y_ + 1) * j - k);
    }
    g[(u32)k] *= _ * inv[k];
  }
  return g;
}
template <template <class... Ts> class ccore, class mint, class... args>
CEXP auto pow_fpssp(poly<ccore, mint, args...> CR p, u64 y, u32 n = 0) NE {
  if (!n) n = (u32)p.size();
  return pow_fpssp(p, y, gen_inv(n, mint::mod()), n);
}

}  // namespace tifa_libs::math

#endif