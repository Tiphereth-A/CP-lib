#ifndef TIFALIBS_POLY_CTSH_FPS
#define TIFALIBS_POLY_CTSH_FPS

#include "../comb/gen_ifact.hpp"
#include "poly.hpp"

namespace tifa_libs::math {

template <template <class... Ts> class ccore, class mint, class... args>
CEXP poly<ccore, mint, args...> ctsh_fps(poly<ccore, mint, args...> CR f, mint c, spnuu ifact, u32 m = 0) {
  using poly_t = poly<ccore, mint, args...>;
  const u32 n = (u32)f.size(), k = n - 1;
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
    auto pref = ctsh_fps(f, mint(t), ifact, u32(mint::mod() - t)), suf = ctsh_fps(f, mint(0), ifact, m - (u32)pref.size());
    std::ranges::copy(suf, std::back_inserter(pref));
    return pref;
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
template <template <class... Ts> class ccore, class mint, class... args>
CEXP poly<ccore, mint, args...> ctsh_fps(poly<ccore, mint, args...> CR f, mint c, u32 m = 0) { return ctsh_fps(f, c, gen_ifact((u32)f.size(), mint::mod()), m); }

}  // namespace tifa_libs::math

#endif