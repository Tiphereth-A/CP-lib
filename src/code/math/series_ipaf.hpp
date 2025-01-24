#ifndef TIFALIBS_MATH_SERIES_IPAF
#define TIFALIBS_MATH_SERIES_IPAF

#include "../comb/binom.hpp"
#include "qpow.hpp"

namespace tifa_libs::math {

// @param f $f(0),\dots,f(k-1)$, $k\leq n$
// @return $\sum_{i=0}^{\infty}a^if(i)$
template <class mint>
CEXP mint series_ipaf(vec<mint> CR f, cT_(mint) a, binom<mint> CR C) NE {
  if (!a.val()) return f[0];
  u32 K = u32(f.size() - 1);
  vec<mint> g(f.size());
  mint _0 = 1;
  flt_ (u32, i, 0, (u32)g.size()) g[i] = f[i] * _0, _0 *= a;
  flt_ (u32, i, 1, (u32)g.size()) g[i] += g[i - 1];
  mint c = 0, _1 = 1;
  flt_ (u32, i, 0, K + 1) c += C.mCn(K + 1, i) * _1 * g[K - i], _1 *= -a;
  return c / qpow(-a + 1, K + 1);
}
template <class mint>
CEXP mint series_ipaf(vec<mint> CR f, cT_(mint) a) NE {
  if (!a.val()) return f[0];
  return series_ipaf(f, a, binom<mint>((u32)f.size() + 1));
}

}  // namespace tifa_libs::math

#endif