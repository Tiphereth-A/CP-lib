#ifndef TIFALIBS_POLY_POLY_TSH
#define TIFALIBS_POLY_POLY_TSH

#include "../comb/gen_fact.hpp"
#include "../comb/gen_ifact.hpp"
#include "poly.hpp"

namespace tifa_libs::math {

template <class T>
constexpr poly<T> poly_tsh(poly<T> const &f, typename T::value_type c, vec<u64> const &fact, vec<u64> const &ifact) {
  u32 n = f.size();
  if (n == 1) return f;
  poly<T> s = f, p(f.size());
  for (u32 i = 0; i < n; ++i) p[n - i - 1] = f[i] * fact[i];
  {
    typename T::value_type _ = 1;
    for (u32 i = 0; i < n; ++i, _ *= c) s[i] = _ * ifact[i];
  }
  (p *= s).resize(n);
  for (u32 i = 0; i < n; ++i) s[n - i - 1] = p[i] * ifact[n - i - 1];
  return s;
}
template <class T>
constexpr poly<T> poly_tsh(poly<T> const &f, typename T::value_type c) {
  u32 n = f.size();
  if (n == 1) return f;
  return poly_tsh(f, c, gen_fact(n, T::value_type::mod()), gen_ifact(n, T::value_type::mod()));
}

}  // namespace tifa_libs::math

#endif