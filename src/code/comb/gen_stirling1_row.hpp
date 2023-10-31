#ifndef TIFA_LIBS_MATH_GEN_STIRLING1_ROW
#define TIFA_LIBS_MATH_GEN_STIRLING1_ROW

#include "../bit/cntl0.hpp"
#include "../poly/poly.hpp"
#include "../poly/poly_shl.hpp"
#include "../poly/poly_tsh.hpp"
#include "gen_fact.hpp"
#include "gen_ifact.hpp"

namespace tifa_libs::math {

// stirling1[i] = {n \\brace i}, i=0,1,...,n
template <class T, bool with_sgn = true, class mint = typename T::value_type>
inline poly<T> gen_stirling1_row(u32 n, vec<mint> const& fact, vec<mint> const& ifact) {
  if (!n) return poly<T>{1};
  poly<T> f{0, 1};
  if (n == 1) return f;
  for (int i = 30 - bit::cntl0(n); ~i; --i) {
    u32 _ = n >> i;
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
template <class T, bool with_sgn = true, class mint = typename T::value_type>
inline poly<T> gen_stirling1_row(u32 n) { return gen_stirling1_row<T, with_sgn, mint>(n, gen_fact<mint>(n + 1), gen_ifact<mint>(n + 1)); }

}  // namespace tifa_libs::math

#endif