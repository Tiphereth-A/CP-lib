#ifndef TIFA_LIBS_MATH_STIRLING2_ROW_GEN
#define TIFA_LIBS_MATH_STIRLING2_ROW_GEN

#include "../poly/poly.hpp"
#include "ifact_mod_gen.hpp"
#include "pows_mod_gen.hpp"

namespace tifa_libs::math {

// stirling2[i] = {n \\brace i}, i=0,1,...,n
template <class T>
inline poly<T> stirling2_row_gen(u64 n, vec<u64> const& pows, vec<u64> const& ifact) {
  if (!n) return poly<T>{1};
  u64 mod = T::value_type::mod();
  poly<T> a(n + 1), b(n + 1);
  for (usz i = 1; i <= n; ++i) a[i] = mul_mod_u(pows[i], ifact[i], mod);
  for (usz i = 0; i <= n; ++i) b[i] = ((i & 1) ? mod - ifact[i] : ifact[i]);
  a *= b;
  a.resize(n + 1);
  return a;
}
// stirling2[i] = {n \\brace i}, i=0,1,...,n
template <class T>
inline poly<T> stirling2_row_gen(u64 n) { return stirling2_row_gen<T>(n, pows_mod_gen(n + 1, n, T::value_type::mod()), ifact_mod_gen(n + 1, T::value_type::mod())); }

}  // namespace tifa_libs::math

#endif