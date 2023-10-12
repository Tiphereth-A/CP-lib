#ifndef TIFALIBS_POLY_TSH
#define TIFALIBS_POLY_TSH

#include "../comb/fact_mod_gen.hpp"
#include "../comb/ifact_mod_gen.hpp"
#include "poly.hpp"

namespace tifa_libs::math {

template <class T>
inline poly<T> poly_tsh(poly<T> const &f, typename T::value_type c, vec<u64> const &fact, vec<u64> const &ifact) {
  size_t n = f.size();
  if (n == 1) return f;
  poly<T> s = f, p(f.size());
  for (size_t i = 0; i < n; ++i) p[n - i - 1] = f[i] * fact[i];
  {
    typename T::value_type _ = 1;
    for (size_t i = 0; i < n; ++i, _ *= c) s[i] = _ * ifact[i];
  }
  (p *= s).resize(n);
  for (size_t i = 0; i < n; ++i) s[n - i - 1] = p[i] * ifact[n - i - 1];
  return s;
}
template <class T>
inline poly<T> poly_tsh(poly<T> const &f, typename T::value_type c) {
  size_t n = f.size();
  if (n == 1) return f;
  return poly_tsh(f, c, fact_mod_gen(n, T::value_type::mod()), ifact_mod_gen(n, T::value_type::mod()));
}

}  // namespace tifa_libs::math

#endif