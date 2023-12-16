#ifndef TIFALIBS_MATH_GCD128
#define TIFALIBS_MATH_GCD128

#include "../util/abs_constexpr.hpp"
#include "../util/traits.hpp"

namespace tifa_libs::math {

template <uint_c T>
constexpr T gcd_u128(T a, T b) {
  if (!a) return b;
  if (!b) return a;
  const int i = std::countr_zero(a), j = std::countr_zero(b), k = std::min(i, j);
  a >>= i, b >>= j;
  while (1) {
    if (a > b) std::swap(a, b);
    if (!(b -= a)) return a << k;
    b >>= std::countr_zero(b);
  }
}
#pragma GCC diagnostic ignored "-Wsign-conversion"
template <int_c T>
constexpr T gcd_128(T a, T b) { return gcd_u128<to_uint_t<T>>(abs(a), abs(b)); }
#pragma GCC diagnostic warning "-Wsign-conversion"

}  // namespace tifa_libs::math

#endif