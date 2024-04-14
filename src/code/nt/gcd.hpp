#ifndef TIFALIBS_MATH_GCD
#define TIFALIBS_MATH_GCD

#include "../util/traits.hpp"

namespace tifa_libs::math {

// From GCC lib
template <int_c T, int_c U>
constexpr std::common_type_t<T, U> gcd(T a, U b) {
  using W = to_uint_t<std::common_type_t<T, U>>;
  if constexpr (std::is_integral_v<W>) return std::gcd(a, b);
  else {
    W u = abs(a), v = abs(b);
    if (!u || !v) return u ^ v;
    const int i = std::__countr_zero(u), j = std::__countr_zero(v), k = std::min(i, j);
    u >>= i, v >>= j;
    while (1) {
      if (u > v) std::swap(u, v);
      if ((v -= u) == 0) return u << k;
      v >>= std::__countr_zero(v);
    }
  }
}

}  // namespace tifa_libs::math

#endif