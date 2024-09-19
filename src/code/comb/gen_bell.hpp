#ifndef TIFALIBS_COMB_GEN_BELL
#define TIFALIBS_COMB_GEN_BELL

#include "../poly/exp_fps.hpp"
#include "gen_fact.hpp"
#include "gen_ifact.hpp"

namespace tifa_libs::math {

// bell[i] = B_i, i=0,1,...,n
template <class poly, std::same_as<TPN poly::val_t> mint>
CEXP poly gen_bell(u32 n, vec<mint> CR fact, vec<mint> CR ifact) {
  poly b(n + 1);
  fle_ (u32, i, 1, n) b[i] = ifact[i];
  b = exp_fps(b);
  fle_ (u32, i, 1, n) b[i] *= fact[i];
  return b;
}
// bell[i] = B_i, i=0,1,...,n
template <class poly>
CEXP poly gen_bell(u32 n) {
  using mint = TPN poly::val_t;
  return gen_bell<poly>(n, gen_fact<mint>(n + 1), gen_ifact<mint>(n + 1));
}

}  // namespace tifa_libs::math

#endif