#ifndef TIFALIBS_COMB_GEN_STIRLING1_ROW
#define TIFALIBS_COMB_GEN_STIRLING1_ROW

#include "../poly/poly_shl.hpp"
#include "../poly/poly_tsh.hpp"
#include "gen_fact.hpp"
#include "gen_ifact.hpp"

namespace tifa_libs::math {

// stirling1[i] = {n \\brace i}, i=0,1,...,n
template <class poly, bool with_sgn = true>
constexpr poly gen_stirling1_row(u32 n, vec<u64> const& fact, vec<u64> const& ifact) {
  using mint = typename poly::value_type;
  if (!n) return poly{1};
  poly f{0, 1};
  if (n == 1) return f;
  for (int i = 30 - std::countl_zero(n); ~i; --i) {
    u32 _ = n >> i;
    f *= poly_tsh(f, mint(_ / 2), fact, ifact);
    f.resize(f.size() + 1);
    if (_ & 1) f = poly_shl(f, 1) + f * (_ - 1);
  }
  f.resize(n + 1);
  if constexpr (with_sgn)
    for (u32 i = 1 + (n & 1); i <= n; i += 2) f[i] = -f[i];
  return f;
}
// stirling1[i] = {n \\brace i}, i=0,1,...,n
template <class poly, bool with_sgn = true>
constexpr poly gen_stirling1_row(u32 n) {
  using mint = typename poly::value_type;
  return gen_stirling1_row<poly, with_sgn>(n, gen_fact(n + 1, mint::mod()), gen_ifact(n + 1, mint::mod()));
}

}  // namespace tifa_libs::math

#endif