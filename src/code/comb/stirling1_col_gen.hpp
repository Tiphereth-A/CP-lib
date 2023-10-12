#ifndef TIFA_LIBS_MATH_STIRLING1_COL_GEN
#define TIFA_LIBS_MATH_STIRLING1_COL_GEN

#include "../math/inverse.hpp"
#include "../poly/poly.hpp"
#include "../poly/poly_pow.hpp"
#include "fact_mod_gen.hpp"
#include "inv_mod_gen.hpp"

namespace tifa_libs::math {

// stirling1[i] = {i \\brack k}, i=0,1,...,n
template <class T>
inline poly<T> stirling1_col_gen(u64 n, u64 k, vec<u64> const& fact, vec<u64> const& inv) {
  if (n < k) return poly<T>(n + 1);
  poly<T> f(n + 1);
  for (size_t i = 1; i <= n; ++i) f[i] = inv[i];
  f = poly_pow(f, k) * inverse(fact[k], T::value_type::mod());
  for (size_t i = k; i <= n; ++i) f[i] *= fact[i];
  for (size_t i = k; i <= n; ++i) f[i] *= ((i ^ k) & 1 ? -1 : 1);
  return f;
}
// stirling1[i] = {i \\brack k}, i=0,1,...,n
template <class T>
inline poly<T> stirling1_col_gen(u64 n, u64 k) { return stirling1_col_gen<T>(n, k, fact_mod_gen(n + 1, T::value_type::mod()), inv_mod_gen(n + 1, T::value_type::mod())); }

}  // namespace tifa_libs::math

#endif