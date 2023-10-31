#ifndef TIFA_LIBS_MATH_GEN_BELL
#define TIFA_LIBS_MATH_GEN_BELL

#include "../poly/poly.hpp"
#include "../poly/poly_exp.hpp"
#include "gen_fact.hpp"
#include "gen_ifact.hpp"

namespace tifa_libs::math {

// bell[i] = B_i, i=0,1,...,n
template <class T, class mint = typename T::value_type>
inline poly<T> gen_bell(u32 n, vec<mint> const& fact, vec<mint> const& ifact) {
  poly<T> b(n + 1);
  for (u32 i = 1; i <= n; ++i) b[i] = ifact[i];
  b = poly_exp(b);
  for (u32 i = 1; i <= n; ++i) b[i] *= fact[i];
  return b;
}
// bell[i] = B_i, i=0,1,...,n
template <class T, class mint = typename T::value_type>
inline poly<T> gen_bell(u32 n) { return gen_bell<T, mint>(n, gen_fact<mint>(n + 1), gen_ifact<mint>(n + 1)); }

}  // namespace tifa_libs::math

#endif