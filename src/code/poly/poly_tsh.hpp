#ifndef TIFALIBS_POLY_POLY_TSH
#define TIFALIBS_POLY_POLY_TSH

#include "../comb/gen_fact.hpp"
#include "../comb/gen_ifact.hpp"

namespace tifa_libs::math {

template <class poly, std::same_as<typename poly::value_type> mint>
constexpr poly poly_tsh(poly const &f, mint c, vec<u64> const &fact, vec<u64> const &ifact) {
  u32 n = f.size();
  if (n == 1) return f;
  poly s = f, p(f.size());
  for (u32 i = 0; i < n; ++i) p[n - i - 1] = f[i] * fact[i];
  {
    mint _ = 1;
    for (u32 i = 0; i < n; ++i, _ *= c) s[i] = _ * ifact[i];
  }
  (p *= s).resize(n);
  for (u32 i = 0; i < n; ++i) s[n - i - 1] = p[i] * ifact[n - i - 1];
  return s;
}
template <class poly, std::same_as<typename poly::value_type> mint>
constexpr poly poly_tsh(poly const &f, mint c) {
  u32 n = f.size();
  if (n == 1) return f;
  return poly_tsh<poly, mint>(f, c, gen_fact(n, mint::mod()), gen_ifact(n, mint::mod()));
}

}  // namespace tifa_libs::math

#endif