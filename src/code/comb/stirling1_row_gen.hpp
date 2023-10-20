#ifndef TIFA_LIBS_MATH_STIRLING1_ROW_GEN
#define TIFA_LIBS_MATH_STIRLING1_ROW_GEN

#include "../bit/cntl0.hpp"
#include "../poly/poly.hpp"
#include "../poly/poly_shl.hpp"
#include "../poly/poly_tsh.hpp"
#include "fact_mod_gen.hpp"
#include "ifact_mod_gen.hpp"

namespace tifa_libs::math {

// stirling1[i] = {n \\brace i}, i=0,1,...,n
template <class T, bool with_sgn = true>
inline poly<T> stirling1_row_gen(u64 n, vec<u64> const& fact, vec<u64> const& ifact) {
  if (!n) return poly<T>{1};
  poly<T> f{0, 1};
  if (n == 1) return f;
  for (int i = 62 - bit::cntl0(n); ~i; --i) {
    u64 _ = n >> i;
    f *= poly_tsh(f, _ / 2, fact, ifact);
    f.resize(f.size() + 1);
    if (_ & 1) f = poly_shl(f, 1) + f * (_ - 1);
  }
  f.resize(n + 1);
  if constexpr (with_sgn)
    for (usz i = 1 + (n & 1); i <= n; i += 2) f[i] = -f[i];
  return f;
}
// stirling1[i] = {n \\brace i}, i=0,1,...,n
template <class T, bool with_sgn = true>
inline poly<T> stirling1_row_gen(u64 n) { return stirling1_row_gen<T, with_sgn>(n, fact_mod_gen(n + 1, T::value_type::mod()), ifact_mod_gen(n + 1, T::value_type::mod())); }

}  // namespace tifa_libs::math

#endif