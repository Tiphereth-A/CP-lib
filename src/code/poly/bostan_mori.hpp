#ifndef TIFA_LIBS_POLY_BOSTAM_MORI
#define TIFA_LIBS_POLY_BOSTAM_MORI

#include "../bit/cntr0.hpp"
#include "../math/ntt_doubling.hpp"
#include "poly_div.hpp"
#include "poly_inv.hpp"
#include "polydata_convtype.hpp"

namespace tifa_libs::math {

template <class T, class mint = typename T::value_type>
mint bostan_mori(u64 k, poly<T> g, poly<T> f) {
  g.strip();
  mint ret = 0;
  if (f.size() >= g.size()) {
    auto r = poly_div(f, g);
    (f -= r * g).strip();
    if (k < r.size()) ret += r[(u32)k];
  }
  if (f.empty()) return ret;

  if constexpr (T::ccore_type != pdct_NTT) {
    f.resize(g.size() - 1);
    while (k) {
      auto _ = g;
      for (u32 i = 1; i < _.size(); i += 2) _[i] = -_[i];
      auto s = f * _, t = g * _;
      for (u32 i = k & 1; i < s.size(); i += 2) f[i / 2] = s[i];
      for (u32 i = 0; i < t.size(); i += 2) g[i / 2] = t[i];
      k /= 2;
    }
    return ret + f[0];
  } else {
    auto& core = T::ccore;
    core.bzr(g.size() * 2);
    u32 n = core.size() / 2;
    core.dif(f.data()), core.dif(g.data());
    f.resize(2 * n), g.resize(2 * n);
    vec<mint> s(2 * n), t(2 * n);
    vec<u32> btr(n);
    for (u32 i = 0, logn = (u32)bit::cntr0(n); i < (1 << logn); ++i) btr[i] = (btr[i / 2] / 2) + ((i & 1) << (logn - 1));
    mint dw = qpow(core.G.inv(), (mint::mod() - 1) / (2 * n));
    while (k) {
      mint inv2 = (mint::mod() + 1) / 2;
      t.resize(n);
      for (u32 i = 0; i < n; ++i) t[i] = g[i * 2] * g[i * 2 + 1];
      s.resize(n);
      if (k & 1) {
        for (u32 i : btr) {
          s[i] = (f[i * 2] * g[i * 2 + 1] - f[i * 2 + 1] * g[i * 2]) * inv2;
          inv2 *= dw;
        }
      } else
        for (u32 i = 0; i < n; ++i) s[i] = (f[i * 2] * g[i * 2 + 1] + f[i * 2 + 1] * g[i * 2]) * inv2;
      f.data().swap(s), g.data().swap(t);
      if ((k /= 2) < n) break;
      ntt_doubling(core, f.data()), ntt_doubling(core, g.data());
    }
    core.dit(f.data()), core.dit(g.data());
    return ret + (f * poly_inv(g))[(u32)k];
  }
}

}  // namespace tifa_libs::math

#endif