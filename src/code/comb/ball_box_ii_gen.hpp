#ifndef TIFA_LIBS_MATH_BALL_BOX_II_GEN
#define TIFA_LIBS_MATH_BALL_BOX_II_GEN

#include "../poly/poly.hpp"
#include "../poly/poly_exp.hpp"
#include "inv_mod_gen.hpp"

namespace tifa_libs::math {

// f = \\prod_{i=1}^m 1/(1-x^i), deg(f) = n
template <class T>
constexpr poly<T> ball_box_ii_gen(u64 m, u64 n, vec<u64> const& inv) {
  poly<T> f(n + 1);
  for (u64 i = 1; i <= m; ++i)
    for (u64 k = 1; k <= n / i; ++k) f[i * k] += inv[k];
  return poly_exp(f);
}

// f = \\prod_{i=1}^m 1/(1-x^i), deg(f) = n
template <class T>
constexpr poly<T> ball_box_ii_gen(u64 m, u64 n) { return ball_box_ii_gen<T>(m, n, inv_mod_gen(n + 1, T::value_type::mod())); }

}  // namespace tifa_libs::math

#endif