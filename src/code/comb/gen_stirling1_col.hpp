#ifndef TIFALIBS_COMB_GEN_STIRLING1_COL
#define TIFALIBS_COMB_GEN_STIRLING1_COL

#include "../math/inverse.hpp"
#include "../poly/poly.hpp"
#include "../poly/poly_pow.hpp"
#include "gen_fact.hpp"
#include "gen_inv.hpp"

namespace tifa_libs::math {

// stirling1[i] = {i \\brack k}, i=0,1,...,n
template <class T, bool with_sgn = true>
poly<T> gen_stirling1_col(u32 n, u32 k, vec<u64> const& fact, vec<u64> const& inv) {
  if (n < k) return poly<T>(n + 1);
  poly<T> f(n + 1);
  for (u32 i = 1; i <= n; ++i) f[i] = inv[i];
  f = poly_pow(f, k) * inverse(fact[k], T::value_type::mod());
  for (u32 i = k; i <= n; ++i) f[i] *= fact[i];
  if constexpr (with_sgn)
    for (u32 i = k ^ 1; i <= n; i += 2) f[i] = -f[i];
  return f;
}
// stirling1[i] = {i \\brack k}, i=0,1,...,n
template <class T, bool with_sgn = true>
poly<T> gen_stirling1_col(u32 n, u32 k) { return gen_stirling1_col<T, with_sgn>(n, k, gen_fact(n + 1, T::value_type::mod()), gen_inv(n + 1, T::value_type::mod())); }

}  // namespace tifa_libs::math

#endif