#ifndef TIFALIBS_COMB_GEN_STIRLING1_COL
#define TIFALIBS_COMB_GEN_STIRLING1_COL

#include "../poly/poly_pow.hpp"
#include "gen_fact.hpp"
#include "gen_inv.hpp"
#include "gen_invseq.hpp"

namespace tifa_libs::math {

// stirling1[i] = {i \\brack k}, i=0,1,...,n
template <class poly, bool with_sgn = true>
constexpr poly gen_stirling1_col(u32 n, u32 k, vec<u64> const& fact, vec<u64> const& inv, vec<u64> const& invfact) {
  if (n < k) return poly(n + 1);
  poly f(n + 1);
  for (u32 i = 1; i <= n; ++i) f[i] = inv[i];
  f = poly_pow(f, k) * invfact[k];
  for (u32 i = k; i <= n; ++i) f[i] *= fact[i];
  if constexpr (with_sgn)
    for (u32 i = k ^ 1; i <= n; i += 2) f[i] = -f[i];
  return f;
}
// stirling1[i] = {i \\brack k}, i=0,1,...,n
template <class poly, bool with_sgn = true>
constexpr poly gen_stirling1_col(u32 n, u32 k) {
  using mint = typename poly::value_type;
  auto fact = gen_fact(n + 1, mint::mod());
  return gen_stirling1_col<poly, with_sgn>(n, k, fact, gen_inv(n + 1, mint::mod()), gen_invseq(fact, mint::mod()));
}

}  // namespace tifa_libs::math

#endif