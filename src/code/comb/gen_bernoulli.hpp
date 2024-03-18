#ifndef TIFALIBS_COMB_GEN_BERNOULLI
#define TIFALIBS_COMB_GEN_BERNOULLI

#include "../poly/poly_inv.hpp"
#include "gen_fact.hpp"
#include "gen_ifact.hpp"

namespace tifa_libs::math {

// bernoulli[i] = B_i, i=0,1,...,n
template <class poly, std::same_as<typename poly::value_type> mint>
constexpr poly gen_bernoulli(u32 n, vec<mint> const& fact, vec<mint> const& ifact) {
  if (!n) return poly{1};
  poly b(n + 1);
  for (u32 i = 0; i <= n; ++i) b[i] = ifact[i + 1];
  b = poly_inv(b);
  for (u32 i = 1; i <= n; ++i) b[i] *= fact[i];
  return b;
}
// bernoulli[i] = B_i, i=0,1,...,n
template <class poly>
constexpr poly gen_bernoulli(u32 n) {
  using mint = typename poly::value_type;
  return gen_bernoulli<poly>(n, gen_fact<mint>(n + 1), gen_ifact<mint>(n + 2));
}

}  // namespace tifa_libs::math

#endif