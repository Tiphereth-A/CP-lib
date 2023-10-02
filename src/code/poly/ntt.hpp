#ifndef TIFALIBS_POLY_NTT
#define TIFALIBS_POLY_NTT

#include "../util/util.hpp"

#include "../math/proot_u64.hpp"
#include "../math/qpow.hpp"
#include "fft_info.hpp"

namespace tifa_libs::math {

template <class mint>
struct NTT {
  static constexpr u64 MOD = mint::mod();
  static_assert((MOD & 3) == 1, "MOD must be prime with 4k+1");

  constexpr NTT() {}
  template <bool inv = false>
  constexpr void run(vec<mint> &g) {
    size_t n = g.size();
    info.set(n);
    f.resize(n);
    w.resize(n);
    w[0] = 1;
    for (size_t i = 0; i < n; ++i) f[i] = g[info.root[i]];
    for (size_t l = 1; l < n; l <<= 1) {
      mint tG;
      if constexpr (inv) tG = qpow(IG, (MOD - 1) / (l + l));
      else tG = qpow(G, (MOD - 1) / (l + l));
      for (size_t i = 1; i < l; ++i) w[i] = w[i - 1] * tG;
      for (size_t k = 0; k < n; k += l + l)
        for (size_t p = 0; p < l; ++p) {
          mint _ = w[p] * f[k | l | p];
          f[k | l | p] = f[k | p] - _;
          f[k | p] += _;
        }
    }
    if constexpr (inv) {
      const mint in = mint(n).inv();
      for (size_t i = 0; i < n; ++i) g[i] = in * f[i];
    } else g = f;
  }

private:
  const mint G = proot_u64(MOD), IG = G.inv();

  FFT_INFO info;
  vec<mint> f, w;
};

}  // namespace tifa_libs::math

#endif