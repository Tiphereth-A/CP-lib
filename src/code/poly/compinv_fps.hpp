#ifndef TIFALIBS_POLY_COMPINV_FPS
#define TIFALIBS_POLY_COMPINV_FPS

#include "../comb/gen_inv.hpp"
#include "exp_fps.hpp"
#include "ln_fps.hpp"
#include "powem_fps.hpp"
#include "shl_fps.hpp"

namespace tifa_libs::math {

// @return g s.t. $g(f(x)) \equiv x \pmod{\deg(f)+1}$
template <class mint, class ccore>
CEXP poly<mint, ccore> compinv_fps(poly<mint, ccore> CR f, spnuu inv, u32 n = 0) {
  using poly_t = poly<mint, ccore>;
  if (assert(f.size() > 1 && f[0] == 0 && f[1] != 0); !n) n = (u32)f.size();
  if (n < 2) return poly_t{0, f[1].inv()}.pre(n);
  poly_t h = powem_fps(f) * (n - 1);
  flt_ (u32, k, 1, n) h[k] *= inv[k];
  h.reverse(), h *= h[0].inv();
  poly_t g = exp_fps(ln_fps(h) * (-mint{n - 1}).inv());
  return g *= f[1].inv(), shl_fps(g, 1).pre(n);
}
// @return g s.t. $g(f(x)) \equiv x \pmod{\deg(f)+1}$
template <class mint, class ccore>
CEXP poly<mint, ccore> compinv_fps(poly<mint, ccore> CR f, u32 n = 0) { return compinv_fps(f, gen_inv(f.size(), mint::mod()), n); }

}  // namespace tifa_libs::math

#endif