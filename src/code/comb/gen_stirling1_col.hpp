#ifndef TIFALIBS_COMB_GEN_STIRLING1_COL
#define TIFALIBS_COMB_GEN_STIRLING1_COL

#include "../poly/pow_fps.hpp"
#include "gen_fact.hpp"
#include "gen_inv.hpp"
#include "gen_invseq.hpp"

namespace tifa_libs::math {

// stirling1[i] = {i \\brack k}, i=0,1,...,n
template <class poly, bool with_sgn = true>
CEXP poly gen_stirling1_col(u32 n, u32 k, vecu64 CR fact, vecu64 CR inv, vecu64 CR invfact) {
  if (n < k) return poly(n + 1);
  poly f(n + 1);
  fle_ (u32, i, 1, n) f[i] = inv[i];
  f = pow_fps(f, k) * invfact[k];
  fle_ (u32, i, k, n) f[i] *= fact[i];
  if CEXP (with_sgn)
    for (u32 i = k ^ 1; i <= n; i += 2) f[i] = -f[i];
  return f;
}
// stirling1[i] = {i \\brack k}, i=0,1,...,n
template <class poly, bool with_sgn = true>
CEXP poly gen_stirling1_col(u32 n, u32 k) {
  using mint = TPN poly::value_type;
  auto fact = gen_fact(n + 1, mint::mod());
  return gen_stirling1_col<poly, with_sgn>(n, k, fact, gen_inv(n + 1, mint::mod()), gen_invseq(fact, mint::mod()));
}

}  // namespace tifa_libs::math

#endif