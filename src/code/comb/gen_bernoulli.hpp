#ifndef TIFA_LIBS_MATH_GEN_BERNOULLI
#define TIFA_LIBS_MATH_GEN_BERNOULLI

#include "../poly/poly.hpp"
#include "../poly/poly_inv.hpp"
#include "gen_fact.hpp"
#include "gen_ifact.hpp"

namespace tifa_libs::math {

// bernoulli[i] = B_i, i=0,1,...,n
template <class T, class mint = typename T::value_type>
poly<T> gen_bernoulli(u32 n, vec<mint> const& fact, vec<mint> const& ifact) {
  if (!n) return poly<T>{1};
  poly<T> b(n + 1);
  for (u32 i = 0; i <= n; ++i) b[i] = ifact[i + 1];
  b = poly_inv(b);
  for (u32 i = 1; i <= n; ++i) b[i] *= fact[i];
  return b;
}
// bernoulli[i] = B_i, i=0,1,...,n
template <class T, class mint = typename T::value_type>
poly<T> gen_bernoulli(u32 n) { return gen_bernoulli<T, mint>(n, gen_fact<mint>(n + 1), gen_ifact<mint>(n + 2)); }

}  // namespace tifa_libs::math

#endif