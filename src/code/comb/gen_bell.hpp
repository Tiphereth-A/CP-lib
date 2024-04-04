#ifndef TIFALIBS_COMB_GEN_BELL
#define TIFALIBS_COMB_GEN_BELL

#include "../poly/exp_fps.hpp"
#include "gen_fact.hpp"
#include "gen_ifact.hpp"

namespace tifa_libs::math {

// bell[i] = B_i, i=0,1,...,n
template <class poly, std::same_as<typename poly::value_type> mint>
constexpr poly gen_bell(u32 n, vec<mint> const& fact, vec<mint> const& ifact) {
  poly b(n + 1);
  for (u32 i = 1; i <= n; ++i) b[i] = ifact[i];
  b = exp_fps(b);
  for (u32 i = 1; i <= n; ++i) b[i] *= fact[i];
  return b;
}
// bell[i] = B_i, i=0,1,...,n
template <class poly>
constexpr poly gen_bell(u32 n) {
  using mint = typename poly::value_type;
  return gen_bell<poly, mint>(n, gen_fact<mint>(n + 1), gen_ifact<mint>(n + 1));
}

}  // namespace tifa_libs::math

#endif