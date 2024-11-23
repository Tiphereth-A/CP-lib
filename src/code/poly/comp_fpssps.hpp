#ifndef TIFALIBS_POLY_COMP_FPSSPS
#define TIFALIBS_POLY_COMP_FPSSPS

#include "../comb/gen_fact.hpp"
#include "../comb/gen_ifact.hpp"
#include "../conv/conv_subset.hpp"
#include "tsh_fps.hpp"

namespace tifa_libs::math {

// @return $f(g(x_0, \dots, x_{n-1}))$
template <class poly, u32 N = 21>
auto comp_fpssps(u32 n, poly f, vec<TPN poly::val_t> g, spnuu fact, spnuu ifact) {
  using mint = TPN poly::val_t;
  static conv_subset<mint, N> ss;
  if (assert(n <= N); !f.size()) return vec<mint>(1 << n);
  if (g[0] != 0) f = tsh_fps(f, g[0], fact, ifact), g[0] = 0;
  f.resize(n + 1), g.resize(1 << n);
  flt_ (u32, i, 0, n + 1) f[i] *= fact[i];
  v3ec<mint> h(n + 1, vvec<mint>(n + 1, vec<mint>(1)));
  flt_ (u32, i, 0, n + 1) h[0][i][0] = f[i];
  flt_ (u32, k, 1, n + 1) {
    auto A = ss.lift({g.begin() + (1 << (k - 1)), g.begin() + (1 << k)});
    ss.zeta(A);
    flt_ (u32, j, 0, n - k + 1) {
      h[k][j] = h[k - 1][j];
      auto B = ss.lift(h[k - 1][j + 1]);
      ss.zeta(B), ss.prod(B, A), ss.mobius(B);
      auto c = ss.unlift(B);
      std::ranges::copy(c, std::back_inserter(h[k][j]));
    }
  }
  return h[n][0];
}
// @return $f(g(x_0, \dots, x_{n-1}))$
template <class poly, u32 N = 21>
CEXP auto comp_fpssps(u32 n, poly CR f, vec<TPN poly::val_t> CR g) {
  using mint = TPN poly::val_t;
  return comp_fpssps<poly, N>(n, f, g, gen_fact(max((u32)f.size(), n) + 1, mint::mod()), gen_ifact(max((u32)f.size(), n) + 1, mint::mod()));
}

}  // namespace tifa_libs::math

#endif