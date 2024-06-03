#ifndef TIFALIBS_POLY_TSH_FPS
#define TIFALIBS_POLY_TSH_FPS

#include "../comb/gen_fact.hpp"
#include "../comb/gen_ifact.hpp"
#include "poly.hpp"

namespace tifa_libs::math {

template <class mint, class ccore>
CEXP poly<mint, ccore> tsh_fps(poly<mint, ccore> CR f, mint c, spnuu fact, spnuu ifact) {
  const u32 n = f.size();
  if (n == 1) return f;
  poly<mint, ccore> s = f, p(f.size());
  flt_ (u32, i, 0, n) p[n - i - 1] = f[i] * fact[i];
  mint _ = 1;
  for (u32 i = 0; i < n; ++i, _ *= c) s[i] = _ * ifact[i];
  (p *= s).resize(n);
  flt_ (u32, i, 0, n) s[n - i - 1] = p[i] * ifact[n - i - 1];
  return s;
}
template <class mint, class ccore>
CEXP poly<mint, ccore> tsh_fps(poly<mint, ccore> CR f, mint c) {
  const u32 n = f.size();
  if (n == 1) return f;
  return tsh_fps<mint, ccore>(f, c, gen_fact(n, mint::mod()), gen_ifact(n, mint::mod()));
}

}  // namespace tifa_libs::math

#endif