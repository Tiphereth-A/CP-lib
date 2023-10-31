#ifndef TIFA_LIBS_MATH_GEN_BERNOULLI
#define TIFA_LIBS_MATH_GEN_BERNOULLI

#include "../poly/poly.hpp"
#include "../poly/poly_inv.hpp"
#include "gen_fact.hpp"
#include "gen_ifact.hpp"

namespace tifa_libs::math {

// bernoulli[i] = B_i, i=0,1,...,n
template <class T>
inline poly<T> gen_bernoulli(u64 n, vec<u64> const& fact, vec<u64> const& ifact) {
  if (!n) return poly<T>{1};
  poly<T> b(n + 1);
  for (usz i = 0; i <= n; ++i) b[i] = ifact[i + 1];
  b = poly_inv(b);
  for (usz i = 1; i <= n; ++i) b[i] *= fact[i];
  return b;
}
// bernoulli[i] = B_i, i=0,1,...,n
template <class T>
inline poly<T> gen_bernoulli(u64 n) { return gen_bernoulli<T>(n, gen_fact(n + 1, T::value_type::mod()), gen_ifact(n + 2, T::value_type::mod())); }

}  // namespace tifa_libs::math

#endif