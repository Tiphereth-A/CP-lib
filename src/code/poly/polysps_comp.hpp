#ifndef TIFALIBS_POLYSPS_COMP
#define TIFALIBS_POLYSPS_COMP

#include "../comb/fact_mod_gen.hpp"
#include "../comb/ifact_mod_gen.hpp"
#include "../conv/conv_subset.hpp"
#include "poly.hpp"
#include "poly_tsh.hpp"

namespace tifa_libs::math {

template <class T, size_t N = 21>
inline vec<typename T::value_type> polysps_comp(size_t n, poly<T> f, vec<typename T::value_type> g, vec<u64> const &fact, vec<u64> const &ifact) {
  assert(n <= N);
  using mint = typename T::value_type;
  static conv_subset<mint, N> ss;
  if (!f.size()) return vec<mint>(1 << n);
  if (g[0] != 0) {
    f = poly_tsh(f, g[0], fact, ifact);
    g[0] = 0;
  }
  f.resize(n + 1);
  g.resize(1 << n);
  for (size_t i = 0; i <= n; ++i) f[i] *= fact[i];
  vvvec<mint> h(n + 1, vvec<mint>(n + 1, vec<mint>{}));
  for (size_t i = 0; i <= n; ++i) h[0][i] = {f[i]};
  for (size_t k = 1; k <= n; ++k) {
    auto A = ss.lift({g.begin() + (1 << (k - 1)), g.begin() + (1 << k)});
    ss.zeta(A);
    for (size_t j = 0; j <= n - k; ++j) {
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
template <class T, size_t N = 21>
inline auto polysps_comp(size_t n, poly<T> const &f, vec<typename T::value_type> const &g) { return polysps_comp<T, N>(n, f, g, fact_mod_gen(f.size(), T::value_type::mod()), ifact_mod_gen(f.size(), T::value_type::mod())); }

}  // namespace tifa_libs::math

#endif