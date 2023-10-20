#ifndef TIFA_LIBS_MATH_BERNOULLI_GEN
#define TIFA_LIBS_MATH_BERNOULLI_GEN

#include "../poly/poly.hpp"
#include "../poly/poly_inv.hpp"
#include "fact_mod_gen.hpp"
#include "ifact_mod_gen.hpp"

namespace tifa_libs::math {

// bernoulli[i] = B_i, i=0,1,...,n
template <class T>
inline poly<T> bernoulli_gen(u64 n, vec<u64> const& fact, vec<u64> const& ifact) {
  if (!n) return poly<T>{1};
  poly<T> b(n + 1);
  for (usz i = 0; i <= n; ++i) b[i] = ifact[i + 1];
  b = poly_inv(b);
  for (usz i = 1; i <= n; ++i) b[i] *= fact[i];
  return b;
}
// bernoulli[i] = B_i, i=0,1,...,n
template <class T>
inline poly<T> bernoulli_gen(u64 n) { return bernoulli_gen<T>(n, fact_mod_gen(n + 1, T::value_type::mod()), ifact_mod_gen(n + 2, T::value_type::mod())); }

}  // namespace tifa_libs::math

#endif