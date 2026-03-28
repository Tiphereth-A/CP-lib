#pragma once

#include "../../comb/seq/inv/lib.hpp"
#include "../../fps/shl/lib.hpp"
#include "../../fps/shr/lib.hpp"
#include "../../math/qpow/basic/lib.hpp"
#include "../polysp/lib.hpp"

namespace tifa_libs {

template <poly_c poly_t, class T>
CEXP auto pow_fpssp(poly_t CR p, u64 y, vec<T> CR inv, u32 n = 0) NE {
  using mint = TPN poly_t::val_t;
  if (!n) n = (u32)p.size();
  if (!y) return poly_t{1}.pre(n);
  if (p.is_zero()) return p.pre(n);
  const u32 l0 = u32(find_if(p, [](cT_(mint) x) NE { return x.val() != 0; }) - begin(p));
  if ((u128)l0 * y >= n) return poly_t(n);
  if (l0) {
    auto _ = shr_fps(p, l0), g = pow_fpssp(_, y, inv, u32(n - l0 * y));
    g.resize(n);
    return shl_fps(g, l0 * y);
  }
  auto ps = poly2sp(p, n);
  poly_t g(n);
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
template <poly_c poly_t>
CEXP auto pow_fpssp(poly_t CR p, u64 y, u32 n = 0) NE {
  if (!n) n = (u32)p.size();
  return pow_fpssp(p, y, gen_inv(n, poly_t::val_t::mod()), n);
}

}  // namespace tifa_libs
