#pragma once

#include "../../comb/seq/fact/lib.hpp"
#include "../../comb/seq/ifact/lib.hpp"
#include "../ds/poly_c/lib.hpp"

namespace tifa_libs {

template <poly_c poly_t, class T>
CEXP auto tsh_fps(poly_t CR f, TPN poly_t::val_t c, vec<T> CR fact, vec<T> CR ifact) NE {
  const u32 n = (u32)f.size();
  retif_((n == 1) [[unlikely]], f);
  poly_t s = f, p((u32)f.size());
  flt_ (u32, i, 0, n) p[n - i - 1] = f[i] * fact[i];
  TPN poly_t::val_t _ = 1;
  for (u32 i = 0; i < n; ++i, _ *= c) s[i] = _ * ifact[i];
  (p *= s).resize(n);
  flt_ (u32, i, 0, n) s[n - i - 1] = p[i] * ifact[n - i - 1];
  return s;
}
template <poly_c poly_t>
CEXP auto tsh_fps(poly_t CR f, TPN poly_t::val_t c) NE {
  const u32 n = (u32)f.size();
  retif_((n == 1) [[unlikely]], f);
  return tsh_fps(f, c, gen_fact(n, poly_t::val_t::mod()), gen_ifact(n, poly_t::val_t::mod()));
}

}  // namespace tifa_libs
