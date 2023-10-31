#ifndef TIFA_LIBS_MATH_GEN_STIRLING1_COL
#define TIFA_LIBS_MATH_GEN_STIRLING1_COL

#include "../poly/poly.hpp"
#include "../poly/poly_pow.hpp"
#include "gen_fact.hpp"
#include "gen_inv.hpp"

namespace tifa_libs::math {

// stirling1[i] = {i \\brack k}, i=0,1,...,n
template <class T, bool with_sgn = true, class mint = typename T::value_type>
inline poly<T> gen_stirling1_col(u32 n, u32 k, vec<mint> const& fact, vec<mint> const& inv) {
  if (n < k) return poly<T>(n + 1);
  poly<T> f(n + 1);
  for (u32 i = 1; i <= n; ++i) f[i] = inv[i];
  f = poly_pow(f, k) * fact[k].inv();
  for (u32 i = k; i <= n; ++i) f[i] *= fact[i];
  if constexpr (with_sgn)
    for (u32 i = k ^ 1; i <= n; i += 2) f[i] = -f[i];
  return f;
}
// stirling1[i] = {i \\brack k}, i=0,1,...,n
template <class T, bool with_sgn = true, class mint = typename T::value_type>
inline poly<T> gen_stirling1_col(u32 n, u32 k) { return gen_stirling1_col<T, with_sgn, mint>(n, k, gen_fact<mint>(n + 1), gen_inv<mint>(n + 1)); }

}  // namespace tifa_libs::math

#endif