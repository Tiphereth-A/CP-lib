#ifndef TIFA_LIBS_MATH_GEN_STIRLING2_ROW
#define TIFA_LIBS_MATH_GEN_STIRLING2_ROW

#include "../poly/poly.hpp"
#include "gen_ifact.hpp"
#include "gen_pows.hpp"

namespace tifa_libs::math {

// stirling2[i] = {n \\brace i}, i=0,1,...,n
template <class T, class mint = typename T::value_type>
inline poly<T> gen_stirling2_row(u32 n, vec<mint> const& pows, vec<mint> const& ifact) {
  if (!n) return poly<T>{1};
  u32 mod = T::value_type::mod();
  poly<T> a(n + 1), b(n + 1);
  for (usz i = 1; i <= n; ++i) a[i] = mul_mod_u(pows[i], ifact[i], mod);
  for (usz i = 0; i <= n; ++i) b[i] = ((i & 1) ? mod - ifact[i] : ifact[i]);
  a *= b;
  a.resize(n + 1);
  return a;
}
// stirling2[i] = {n \\brace i}, i=0,1,...,n
template <class T, class mint = typename T::value_type>
inline poly<T> gen_stirling2_row(u32 n) { return gen_stirling2_row<T, mint>(n, gen_pows<mint>(n + 1, n), gen_ifact<mint>(n + 1)); }

}  // namespace tifa_libs::math

#endif