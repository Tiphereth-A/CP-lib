#pragma once

#include "../../comb/seq/ifact/lib.hpp"
#include "../ds/poly_c/lib.hpp"

namespace tifa_libs {

template <poly_c poly_t, class T>
CEXP poly_t ctsh_fps(poly_t CR f, TPN poly_t::val_t c, vec<T> CR ifact, u32 m = 0) NE {
  const u32 n = (u32)f.size(), k = n - 1;
  using mint = TPN poly_t::val_t;
  if (!m) m = n;
  u64 t = c.val();
  if (t <= k) {
    poly_t ret(m);
    u32 ptr = 0;
    for (u32 i = (u32)t; i <= k && ptr < m; ++i) ret[ptr++] = f[i];
    if (k + 1 < t + m) {
      auto suf = ctsh_fps(f, mint(k + 1), ifact, m - ptr);
      flt_ (u64, i, k + 1, t + m) ret[ptr++] = suf[(u32)i - (k + 1)];
    }
    return ret;
  }
  if (t + m > mint::mod()) {
    auto pre = ctsh_fps(f, mint(t), ifact, u32(mint::mod() - t)),
         suf = ctsh_fps(f, mint(0), ifact, m - (u32)pre.size());
    copy(suf, std::back_inserter(pre));
    return pre;
  }
  poly_t d(k + 1);
  flt_ (u32, i, 0, k + 1) {
    d[i] = ifact[i], (d[i] *= ifact[k - i]) *= f[i];
    if ((k - i) & 1) d[i] = -d[i];
  }
  poly_t h(m + k);
  for (u32 i = 0; i < m + k; ++i) h[i] = mint(t - k + i).inv();
  auto dh = d * h;
  poly_t ret(m);
  mint cur = t;
  flt_ (u32, i, 1, k + 1) cur *= t - i;
  flt_ (u32, i, 0, m) ret[i] = cur * dh[k + i], (cur *= t + i + 1) *= h[i];
  return ret;
}
template <poly_c poly_t>
CEXP auto ctsh_fps(poly_t CR f, TPN poly_t::val_t c, u32 m = 0) NE { return ctsh_fps(f, c, gen_ifact((u32)f.size(), poly_t::val_t::mod()), m); }

}  // namespace tifa_libs
