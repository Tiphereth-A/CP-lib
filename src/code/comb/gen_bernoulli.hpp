#ifndef TIFALIBS_COMB_GEN_BERNOULLI
#define TIFALIBS_COMB_GEN_BERNOULLI

#include "../poly/inv_fps.hpp"
#include "gen_fact.hpp"
#include "gen_ifact.hpp"

namespace tifa_libs::math {

// bernoulli[i] = B_i, i=0,1,...,n
template <class poly, class T>
CEXP poly gen_bernoulli(u32 n, vec<T> CR fact, vec<T> CR ifact) NE {
  if (!n) return poly{1};
  poly b(n + 1);
  flt_ (u32, i, 0, n + 1) b[i] = ifact[i + 1];
  b = inv_fps(b);
  flt_ (u32, i, 1, n + 1) b[i] *= fact[i];
  return b;
}
// bernoulli[i] = B_i, i=0,1,...,n
template <class poly>
CEXP poly gen_bernoulli(u32 n) NE {
  using mint = TPN poly::val_t;
  return gen_bernoulli<poly>(n, gen_fact<mint>(n + 1), gen_ifact<mint>(n + 2));
}

}  // namespace tifa_libs::math

#endif