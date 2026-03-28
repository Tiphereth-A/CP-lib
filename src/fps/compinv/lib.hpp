#pragma once

#include "../../comb/seq/inv/lib.hpp"
#include "../exp/lib.hpp"
#include "../ln/lib.hpp"
#include "../powem/lib.hpp"
#include "../shl/lib.hpp"

namespace tifa_libs {

// @return g s.t. $g(f(x)) \equiv x \pmod{\deg(f)+1}$
template <poly_c poly_t, class T>
CEXP auto compinv_fps(poly_t CR f, vec<T> CR inv, u32 n = 0) NE {
  if (assert(f.size() > 1 && f[0] == 0 && f[1] != 0); !n) n = (u32)f.size();
  if (n < 2) return poly_t{0, f[1].inv()}.pre(n);
  poly_t h = powem_fps(f) * (n - 1);
  flt_ (u32, k, 1, n) h[k] *= inv[k];
  h.reverse(), h *= h[0].inv();
  poly_t g = exp_fps(ln_fps(h) * (-TPN poly_t::val_t{n - 1}).inv());
  g *= f[1].inv();
  return shl_fps(g, 1).pre(n);
}
// @return g s.t. $g(f(x)) \equiv x \pmod{\deg(f)+1}$
template <poly_c poly_t>
CEXP auto compinv_fps(poly_t CR f, u32 n = 0) NE { return compinv_fps(f, gen_inv((u32)f.size(), poly_t::val_t::mod()), n); }

}  // namespace tifa_libs
