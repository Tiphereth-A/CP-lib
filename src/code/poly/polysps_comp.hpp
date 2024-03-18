#ifndef TIFALIBS_POLY_POLYSPS_COMP
#define TIFALIBS_POLY_POLYSPS_COMP

#include "../comb/gen_fact.hpp"
#include "../comb/gen_ifact.hpp"
#include "../conv/conv_subset.hpp"
#include "poly_tsh.hpp"

namespace tifa_libs::math {

template <class poly, u32 N = 21, std::same_as<typename poly::value_type> mint>
vec<mint> polysps_comp(u32 n, poly f, vec<mint> g, vec<u64> const &fact, vec<u64> const &ifact) {
  assert(n <= N);
  static conv_subset<mint, N> ss;
  if (!f.size()) return vec<mint>(1 << n);
  if (g[0] != 0) {
    f = poly_tsh(f, g[0], fact, ifact);
    g[0] = 0;
  }
  f.resize(n + 1);
  g.resize(1 << n);
  for (u32 i = 0; i <= n; ++i) f[i] *= fact[i];
  vvvec<mint> h(n + 1, vvec<mint>(n + 1, vec<mint>{}));
  for (u32 i = 0; i <= n; ++i) h[0][i] = {f[i]};
  for (u32 k = 1; k <= n; ++k) {
    auto A = ss.lift({g.begin() + (1 << (k - 1)), g.begin() + (1 << k)});
    ss.zeta(A);
    for (u32 j = 0; j <= n - k; ++j) {
      h[k][j] = h[k - 1][j];
      auto B = ss.lift(h[k - 1][j + 1]);
      ss.zeta(B);
      ss.prod(B, A);
      ss.mobius(B);
      auto c = ss.unlift(B);
      std::copy(c.begin(), c.end(), std::back_inserter(h[k][j]));
    }
  }
  return h[n][0];
}
template <class poly, u32 N = 21, std::same_as<typename poly::value_type> mint>
constexpr auto polysps_comp(u32 n, poly const &f, vec<mint> const &g) { return polysps_comp<poly, N, mint>(n, f, g, gen_fact((u32)f.size() + 1, mint::mod()), gen_ifact((u32)f.size() + 1, mint::mod())); }

}  // namespace tifa_libs::math

#endif