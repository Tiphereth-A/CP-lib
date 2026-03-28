#pragma once

#include "../../../fps/exp/lib.hpp"
#include "../fact/lib.hpp"
#include "../ifact/lib.hpp"

namespace tifa_libs {

// bell[i] = B_i, i=0,1,...,n
template <class poly>
CEXP poly gen_bell(u32 n, vec<TPN poly::val_t> CR fact, vec<TPN poly::val_t> CR ifact) NE {
  poly b(n + 1);
  flt_ (u32, i, 1, n + 1) b[i] = ifact[i];
  b = exp_fps(b);
  flt_ (u32, i, 1, n + 1) b[i] *= fact[i];
  return b;
}
// bell[i] = B_i, i=0,1,...,n
template <class poly>
CEXP poly gen_bell(u32 n) NE {
  using mint = TPN poly::val_t;
  return gen_bell<poly>(n, gen_fact<mint>(n + 1), gen_ifact<mint>(n + 1));
}

}  // namespace tifa_libs
