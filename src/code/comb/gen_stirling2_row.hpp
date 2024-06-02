#ifndef TIFALIBS_COMB_GEN_STIRLING2_ROW
#define TIFALIBS_COMB_GEN_STIRLING2_ROW

#include "gen_ifact.hpp"
#include "gen_pows.hpp"

namespace tifa_libs::math {

// stirling2[i] = {n \\brace i}, i=0,1,...,n
template <class poly>
CEXP poly gen_stirling2_row(u32 n, vecu64 CR pows, vecu64 CR ifact) {
  using mint = TPN poly::value_type;
  if (!n) return poly{1};
  u64 mod = mint::mod();
  poly a(n + 1), b(n + 1);
  fle_ (u32, i, 1, n) a[i] = mul_mod_u(pows[i], ifact[i], mod);
  fle_ (u32, i, 0, n) b[i] = ((i & 1) ? mod - ifact[i] : ifact[i]);
  return (a *= b).resize(n + 1), a;
}
// stirling2[i] = {n \\brace i}, i=0,1,...,n
template <class poly>
CEXP poly gen_stirling2_row(u32 n) {
  using mint = TPN poly::value_type;
  return gen_stirling2_row<poly>(n, gen_pows(n + 1, n, mint::mod()), gen_ifact(n + 1, mint::mod()));
}

}  // namespace tifa_libs::math

#endif