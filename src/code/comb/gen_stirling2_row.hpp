#ifndef TIFALIBS_COMB_GEN_STIRLING2_ROW
#define TIFALIBS_COMB_GEN_STIRLING2_ROW

#include "../poly/poly.hpp"
#include "gen_ifact.hpp"
#include "gen_pows.hpp"

namespace tifa_libs::math {

// stirling2[i] = {n \\brace i}, i=0,1,...,n
template <class T>
constexpr poly<T> gen_stirling2_row(u32 n, vec<u64> const& pows, vec<u64> const& ifact) {
  if (!n) return poly<T>{1};
  u64 mod = T::value_type::mod();
  poly<T> a(n + 1), b(n + 1);
  for (u32 i = 1; i <= n; ++i) a[i] = mul_mod_u(pows[i], ifact[i], mod);
  for (u32 i = 0; i <= n; ++i) b[i] = ((i & 1) ? mod - ifact[i] : ifact[i]);
  a *= b;
  a.resize(n + 1);
  return a;
}
// stirling2[i] = {n \\brace i}, i=0,1,...,n
template <class T>
constexpr poly<T> gen_stirling2_row(u32 n) { return gen_stirling2_row<T>(n, gen_pows(n + 1, n, T::value_type::mod()), gen_ifact(n + 1, T::value_type::mod())); }

}  // namespace tifa_libs::math

#endif