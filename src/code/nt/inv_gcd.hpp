#ifndef TIFALIBS_MATH_INV_GCD
#define TIFALIBS_MATH_INV_GCD

#include "../math/safe_mod.hpp"
#include "exgcd.hpp"

namespace tifa_libs::math {

template <uint_c T>
constexpr ptt<T> inv_gcd(T n, T mod) {
  using U = std::make_signed_t<T>;
  auto [g, x, y] = exgcd(U(n % mod), (U)mod);
  return {g, safe_mod(x, mod)};
}

}  // namespace tifa_libs::math

#endif