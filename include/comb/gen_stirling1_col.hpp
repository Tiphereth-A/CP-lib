#ifndef TIFALIBS_COMB_GEN_STIRLING1_COL
#define TIFALIBS_COMB_GEN_STIRLING1_COL

#include "../math/fact_helper.hpp"
#include "../poly/pow_fps.hpp"
#include "gen_inv.hpp"

namespace tifa_libs::math {

// stirling1[i] = {i \\brack k}, i=0,1,...,n
template <class poly, class T, bool with_sgn = true>
CEXP poly gen_stirling1_col(u32 n, u32 k, vec<T> CR fact, vec<T> CR inv, vec<T> CR ifact) NE {
  if (n < k) return poly(n + 1);
  poly f(n + 1);
  flt_ (u32, i, 1, n + 1) f[i] = inv[i];
  f = pow_fps(f, k) * ifact[k];
  flt_ (u32, i, k, n + 1) f[i] *= fact[i];
  if CEXP (with_sgn)
    for (u32 i = k ^ 1; i <= n; i += 2) f[i] = -f[i];
  return f;
}
// stirling1[i] = {i \\brack k}, i=0,1,...,n
template <class poly, bool with_sgn = true>
CEXP poly gen_stirling1_col(u32 n, u32 k) NE {
  using mint = TPN poly::val_t;
  fact_helper<mint>::ensure(n + 1);
  return gen_stirling1_col<poly, mint, with_sgn>(n, k, fact_helper<mint>::fact, gen_inv<mint>(n + 1), fact_helper<mint>::ifact);
}

}  // namespace tifa_libs::math

#endif