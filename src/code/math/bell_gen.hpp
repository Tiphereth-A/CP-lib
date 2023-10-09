#ifndef TIFA_LIBS_MATH_BELL_GEN
#define TIFA_LIBS_MATH_BELL_GEN

#include "../poly/poly.hpp"
#include "../poly/poly_exp.hpp"
#include "fact_mod_gen.hpp"
#include "ifact_mod_gen.hpp"

namespace tifa_libs::math {

// bell[i] = B_i, i=0,1,...,n
template <class T>
inline poly<T> bell_gen(u64 n) {
  u64 mod = T::value_type::mod();
  vec<u64> fact = fact_mod_gen(n + 1, mod), ifact = ifact_mod_gen(n + 1, mod);
  poly<T> a(n + 1);
  for (size_t i = 0; i <= n; ++i) a[i] = ifact[i];
  a = poly_exp(a);
  for (size_t i = 0; i <= n; ++i) a[i] *= fact[i];
  return a;
}

}  // namespace tifa_libs::math

#endif