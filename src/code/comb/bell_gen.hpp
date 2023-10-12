#ifndef TIFA_LIBS_MATH_BELL_GEN
#define TIFA_LIBS_MATH_BELL_GEN

#include "../poly/poly.hpp"
#include "../poly/poly_exp.hpp"
#include "fact_mod_gen.hpp"
#include "ifact_mod_gen.hpp"

namespace tifa_libs::math {

// bell[i] = B_i, i=0,1,...,n
template <class T>
inline poly<T> bell_gen(u64 n, vec<u64> const& fact, vec<u64> const& ifact) {
  poly<T> b(n + 1);
  for (size_t i = 1; i <= n; ++i) b[i] = ifact[i];
  b = poly_exp(b);
  for (size_t i = 1; i <= n; ++i) b[i] *= fact[i];
  return b;
}
// bell[i] = B_i, i=0,1,...,n
template <class T>
inline poly<T> bell_gen(u64 n) { return bell_gen<T>(n, fact_mod_gen(n + 1, T::value_type::mod()), ifact_mod_gen(n + 1, T::value_type::mod())); }

}  // namespace tifa_libs::math

#endif