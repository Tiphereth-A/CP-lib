#ifndef TIFALIBS_COMB_GEN_BALL_BOX_II
#define TIFALIBS_COMB_GEN_BALL_BOX_II

#include "../poly/exp_fps.hpp"
#include "gen_inv.hpp"

namespace tifa_libs::math {

// f = \\prod_{i=1}^m 1/(1-x^i), deg(f) = n
template <class poly>
CEXP poly gen_ball_box_ii(u32 m, u32 n, spnuu inv) {
  poly f(n + 1);
  flt_ (u32, i, 1, m + 1)
    flt_ (u32, k, 1, n / i + 1) f[i * k] += inv[k];
  return exp_fps(f);
}
// f = \\prod_{i=1}^m 1/(1-x^i), deg(f) = n
template <class poly>
CEXP poly gen_ball_box_ii(u32 m, u32 n) { return gen_ball_box_ii<poly>(m, n, gen_inv(n + 1, poly::val_t::mod())); }

}  // namespace tifa_libs::math

#endif