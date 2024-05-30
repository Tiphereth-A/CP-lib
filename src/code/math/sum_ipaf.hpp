#ifndef TIFALIBS_MATH_SUM_IPAF
#define TIFALIBS_MATH_SUM_IPAF

#include "../comb/binom.hpp"
#include "lagrange_interp0.hpp"
#include "qpow.hpp"

namespace tifa_libs::math {

// @param f $f(0),\dots,f(k-1)$, $k\leq n$
// @return $\sum_{i=0}^{n-1}a^if(i)$
template <class mint>
CEXP mint sum_ipaf(vec<mint> CR f, cT_(mint) a, u64 n, Binom<mint> CR C) {
  if (!n) return mint(0);
  if (!a.val()) return f[0];
  if (a.val() == 1) {
    vec<mint> g(f.size() + 1, mint(0));
    flt_ (u32, i, 1, (u32)g.size()) g[i] = g[i - 1] + f[i - 1];
    return lagrange_interp0(g, n, C.ifact);
  }
  vec<mint> g(f.size());
  mint _0 = 1;
  flt_ (u32, i, 0, (u32)g.size()) g[i] = f[i] * _0, _0 *= a;
  flt_ (u32, i, 1, (u32)g.size()) g[i] += g[i - 1];
  mint c = 0, _1 = 1;
  const u32 K = u32(f.size() - 1);
  fle_ (u32, i, 0, K) c += C.mCn(K + 1, i) * _1 * g[K - i], _1 *= -a;
  c /= qpow(-a + 1, K + 1);
  mint _2 = 1, ia = a.inv();
  flt_ (u32, i, 0, (u32)g.size()) g[i] = (g[i] - c) * _2, _2 *= ia;
  return lagrange_interp0(g, n - 1, C.ifact) * qpow(a, n - 1) + c;
}
template <class mint>
CEXP mint sum_ipaf(vec<mint> CR f, cT_(mint) a, u64 n) {
  if (!n) return mint(0);
  if (!a.val()) return f[0];
  return sum_ipaf(f, a, n, Binom<mint>((u32)(f.size() + 1)));
}

}  // namespace tifa_libs::math

#endif