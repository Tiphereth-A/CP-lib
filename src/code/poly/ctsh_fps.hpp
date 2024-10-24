#ifndef TIFALIBS_POLY_CTSH_FPS
#define TIFALIBS_POLY_CTSH_FPS

#include "../comb/gen_ifact.hpp"
#include "poly.hpp"

namespace tifa_libs::math {

template <class mint, class ccore>
CEXP poly<mint, ccore> ctsh_fps(poly<mint, ccore> CR f, mint c, spnuu ifact, u32 m = 0) {
  using poly_t = poly<mint, ccore>;
  const u32 n = f.size(), k = f.size() - 1;
  if (!m) m = n;
  u64 t = c.val();
  if (t <= k) {
    poly_t ret(m);
    u32 ptr = 0;
    for (u32 i = (u32)t; i <= k && ptr < m; ++i) ret[ptr++] = f[i];
    if (k + 1 < t + m) {
      auto suf = ctsh_fps<mint, ccore>(f, k + 1, ifact, m - ptr);
      flt_ (u64, i, k + 1, t + m) ret[ptr++] = suf[(u32)i - (k + 1)];
    }
    return ret;
  }
  if (t + m > mint::mod()) {
    auto pref = ctsh_fps<mint, ccore>(f, t, ifact, u32(mint::mod() - t)), suf = ctsh_fps<mint, ccore>(f, 0, ifact, m - pref.size());
    std::ranges::copy(suf.data(), std::back_inserter(pref.data()));
    return pref;
  }
  poly_t d(k + 1);
  fle_ (u32, i, 0, k) {
    d[i] = ifact[i], (d[i] *= ifact[k - i]) *= f[i];
    if ((k - i) & 1) d[i] = -d[i];
  }
  poly_t h(m + k);
  for (u32 i = 0; i < m + k; ++i) h[i] = mint(t - k + i).inv();
  auto dh = d * h;
  poly_t ret(m);
  mint cur = t;
  fle_ (u32, i, 1, k) cur *= t - i;
  flt_ (u32, i, 0, m) ret[i] = cur * dh[k + i], (cur *= t + i + 1) *= h[i];
  return ret;
}
template <class mint, class ccore>
CEXP poly<mint, ccore> ctsh_fps(poly<mint, ccore> CR f, mint c, u32 m = 0) { return ctsh_fps<mint, ccore>(f, c, gen_ifact(f.size(), mint::mod()), m); }

}  // namespace tifa_libs::math

#endif