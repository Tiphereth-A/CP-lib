#ifndef TIFALIBS_COMB_GEN_STIRLING2_ROW
#define TIFALIBS_COMB_GEN_STIRLING2_ROW

#include "gen_ifact.hpp"
#include "gen_pows.hpp"

namespace tifa_libs::math {

// stirling2[i] = {n \\brace i}, i=0,1,...,n
template <class poly>
CEXP poly gen_stirling2_row(u32 n, spnuu pows, spnuu ifact) NE {
  using mint = TPN poly::val_t;
  retif_((!n) [[unlikely]], poly{1});
  u64 mod = mint::mod();
  poly a(n + 1), b(n + 1);
  flt_ (u32, i, 1, n + 1) a[i] = mul_mod_u(pows[i], ifact[i], mod);
  flt_ (u32, i, 0, n + 1) b[i] = ((i & 1) ? mod - ifact[i] : ifact[i]);
  (a *= b).resize(n + 1);
  return a;
}
// stirling2[i] = {n \\brace i}, i=0,1,...,n
template <class poly>
CEXP poly gen_stirling2_row(u32 n) NE {
  using mint = TPN poly::val_t;
  return gen_stirling2_row<poly>(n, gen_pows(n + 1, n, mint::mod()), gen_ifact(n + 1, mint::mod()));
}

}  // namespace tifa_libs::math

#endif