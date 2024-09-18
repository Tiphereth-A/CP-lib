#ifndef TIFALIBS_POLY_COMP_FPS
#define TIFALIBS_POLY_COMP_FPS

#include "inv_fps.hpp"

namespace tifa_libs::math {

// @return g(f(x))
template <class mint, class ccore>
CEXP poly<mint, ccore> comp_fps(poly<mint, ccore> f, poly<mint, ccore> g) {
  using poly_t = poly<mint, ccore>;
  auto& core = poly<mint, ccore>::conv_core;
  auto dfs = [&](auto&& dfs, poly_t b, u32 n, u32 h, u32 k) -> poly_t {
    if (!n) {
      poly_t _{b.data().begin(), b.data().begin() + k};
      _.data().push_back(1), _.reverse(), (_ = inv_fps(_)).reverse();
      poly_t g_ = g * _, a(k * h);
      flt_ (u32, i, 0, (u32)g.size()) a[k - i - 1] = g_[i + k];
      return a;
    }
    poly_t bb(k * h * 4), cc(k * h * 2);
    flt_ (u32, i, 0, k) std::copy(b.data().begin() + i * h, b.data().begin() + i * h + n + 1, bb.data().begin() + i * h * 2);
    bb[k * h * 2] += 1, core.bzr(k * h * 4), core.dif(bb.data());
    for (u32 i = 0; i < k * h * 4; i += 2) swap(bb[i], bb[i + 1]);
    flt_ (u32, i, 0, k * h * 2) cc[i] = bb[i * 2] * bb[i * 2 + 1];
    core.bzr(k * h * 2), core.dit(cc.data()), cc[0] -= 1, b.data().assign(k * h, 0);
    flt_ (u32, i, 0, k * 2)
      fle_ (u32, j, 0, n / 2) b[i * h / 2 + j] = cc[i * h + j];
    poly_t a = dfs(dfs, b, n / 2, h / 2, k * 2), aa(k * h * 4);
    flt_ (u32, i, 0, k * 2)
      fle_ (u32, j, 0, n / 2) aa[(i * h + j) * 2 + n % 2] = a[i * h / 2 + j];
    core.bzr(k * h * 4), core.dif(aa.data());
    for (u32 i = 1; i < k * h * 4; i *= 2) std::reverse(bb.data().begin() + i, bb.data().begin() + i * 2);
    flt_ (u32, i, 0, k * h * 4) aa[i] *= bb[i];
    core.dit(aa.data()), a.data().assign(k * h, 0);
    flt_ (u32, i, 0, k) std::copy(aa.data().begin() + i * h * 2, aa.data().begin() + i * h * 2 + n + 1, a.data().begin() + i * h);
    return a;
  };
  const u32 n = max(f.size(), g.size()), h = std::bit_ceil(n );
  poly_t b(h);
  auto _ = g[0];
  f.resize(n), g.resize(n), g[0] = 0;
  flt_ (u32, i, 0, n) b[i] = -f[i];
  poly_t a = dfs(dfs, b, n - 1, h, 1).pre(n);
  return a.reverse(), a[0] += _, a;
}
}  // namespace tifa_libs::math

#endif