#ifndef TIFA_LIBS_MATH_SUM_IPAF
#define TIFA_LIBS_MATH_SUM_IPAF

#include "../comb/binom.hpp"
#include "lagrange_interp0.hpp"
#include "qpow.hpp"

namespace tifa_libs::math {

// @param f $f(0),\dots,f(k-1)$, $k\leq n$
// @return $\sum_{i=0}^{n-1}a^if(i)$
template <class mint>
mint sum_ipaf(vec<mint> const& f, mint const& a, u64 n, Binom<mint> const& C) {
  if (!n) return mint(0);
  if (!a.val()) return f[0];
  if (a.val() == 1) {
    vec<mint> g(f.size() + 1, mint(0));
    for (u32 i = 1; i < g.size(); ++i) g[i] = g[i - 1] + f[i - 1];
    return lagrange_interp0(g, n, C.ifact);
  }
  vec<mint> g(f.size());
  mint buf = 1;
  for (u32 i = 0; i < g.size(); ++i) g[i] = f[i] * buf, buf *= a;
  for (u32 i = 1; i < g.size(); ++i) g[i] += g[i - 1];
  mint c = 0, buf2 = 1;
  u32 K = u32(f.size() - 1);
  for (u32 i = 0; i <= K; ++i) c += C.mCn(K + 1, i) * buf2 * g[K - i], buf2 *= -a;
  c /= qpow(-a + 1, K + 1);
  mint buf3 = 1, ia = a.inv();
  for (u32 i = 0; i < g.size(); ++i) g[i] = (g[i] - c) * buf3, buf3 *= ia;
  return lagrange_interp0(g, n - 1, C.ifact) * qpow(a, n - 1) + c;
}
template <class mint>
mint sum_ipaf(vec<mint> const& f, mint const& a, u64 n) {
  if (!n) return mint(0);
  if (!a.val()) return f[0];
  return sum_ipaf(f, a, n, Binom<mint>((u32)(f.size() + 1)));
}

}  // namespace tifa_libs::math

#endif