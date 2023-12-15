#ifndef TIFALIBS_MATH_SERIES_IPAF
#define TIFALIBS_MATH_SERIES_IPAF

#include "../comb/binom.hpp"
#include "qpow.hpp"

namespace tifa_libs::math {

// @param f $f(0),\dots,f(k-1)$, $k\leq n$
// @return $\sum_{i=0}^{\infty}a^if(i)$
template <class mint>
constexpr mint series_ipaf(vec<mint> const& f, mint const& a, Binom<mint> const& C) {
  if (!a.val()) return f[0];
  u32 K = u32(f.size() - 1);
  vec<mint> g(f.size());
  mint buf = 1;
  for (u32 i = 0; i < g.size(); ++i) g[i] = f[i] * buf, buf *= a;
  for (u32 i = 1; i < g.size(); ++i) g[i] += g[i - 1];
  mint c = 0, buf2 = 1;
  for (u32 i = 0; i <= K; ++i) c += C.mCn(K + 1, i) * buf2 * g[K - i], buf2 *= -a;
  return c / qpow(-a + 1, K + 1);
}
template <class mint>
constexpr mint series_ipaf(vec<mint> const& f, mint const& a) {
  if (!a.val()) return f[0];
  return series_ipaf(f, a, Binom<mint>((u32)f.size() + 1));
}

}  // namespace tifa_libs::math

#endif