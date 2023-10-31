#ifndef TIFA_LIBS_MATH_GEN_BELL
#define TIFA_LIBS_MATH_GEN_BELL

#include "../poly/poly.hpp"
#include "../poly/poly_exp.hpp"
#include "gen_fact.hpp"
#include "gen_ifact.hpp"

namespace tifa_libs::math {

// bell[i] = B_i, i=0,1,...,n
template <class T>
inline poly<T> gen_bell(u64 n, vec<u64> const& fact, vec<u64> const& ifact) {
  poly<T> b(n + 1);
  for (usz i = 1; i <= n; ++i) b[i] = ifact[i];
  b = poly_exp(b);
  for (usz i = 1; i <= n; ++i) b[i] *= fact[i];
  return b;
}
// bell[i] = B_i, i=0,1,...,n
template <class T>
inline poly<T> gen_bell(u64 n) { return gen_bell<T>(n, gen_fact(n + 1, T::value_type::mod()), gen_ifact(n + 1, T::value_type::mod())); }

}  // namespace tifa_libs::math

#endif