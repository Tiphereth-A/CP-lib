#ifndef TIFALIBS_POLY_POW_FPSSP
#define TIFALIBS_POLY_POW_FPSSP

#include "../comb/gen_inv.hpp"
#include "../math/qpow.hpp"
#include "polysp.hpp"
#include "shl_fps.hpp"
#include "shr_fps.hpp"

namespace tifa_libs::math {

template <class mint, class ccore>
constexpr poly<mint, ccore> pow_fpssp(poly<mint, ccore> const& p, u64 y, vecu64 const& inv, u32 n = 0) {
  if (!n) n = p.size();
  if (!y) return poly<mint, ccore>{1}.pre(n);
  if (p.data().empty()) return p.pre(n);
  u32 l0 = u32(std::ranges::find_if(p.data(), [](auto const& x) { return x != 0; }) - p.data().begin());
  if ((u128)l0 * y >= n) return poly<mint, ccore>(n);
  if (l0) {
    auto _ = shr_fps(p, l0), g = pow_fpssp(_, y, inv, n - l0 * y);
    g.resize(n);
    return shl_fps(g, l0 * y);
  }
  auto ps = poly2sp(p, n);
  poly<mint, ccore> g(n);
  g[0] = qpow(p[0], y);
  auto _ = p[0].inv();
  for (u64 k = 1, y_ = y % mint::mod(); k < n; ++k) {
    for (auto& [j, pj] : ps) {
      if (k < j) break;
      g[k] += pj * g[k - j] * ((y_ + 1) * j - k);
    }
    g[k] *= _ * inv[k];
  }
  return g;
}
template <class mint, class ccore>
constexpr poly<mint, ccore> pow_fpssp(poly<mint, ccore> const& p, u64 y, u32 n = 0) {
  if (!n) n = p.size();
  return pow_fpssp(p, y, gen_inv(n, mint::mod()), n);
}

}  // namespace tifa_libs::math

#endif