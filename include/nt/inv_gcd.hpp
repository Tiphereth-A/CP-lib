#ifndef TIFALIBS_MATH_INV_GCD
#define TIFALIBS_MATH_INV_GCD

#include "../math/safe_mod.hpp"
#include "../util/alias_others.hpp"
#include "exgcd.hpp"

namespace tifa_libs::math {

template <uint_c T>
CEXP ptt<T> inv_gcd(T n, T mod) NE {
  using U = to_sint_t<T>;
  auto [g, x] = exgcd<U, true>(U(n % mod), (U)mod);
  return {g, safe_mod(x, mod)};
}

}  // namespace tifa_libs::math

#endif