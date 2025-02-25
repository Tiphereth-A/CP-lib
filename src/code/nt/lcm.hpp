#ifndef TIFALIBS_MATH_LCM
#define TIFALIBS_MATH_LCM

#include "gcd.hpp"

namespace tifa_libs::math {

template <int_c T, int_c U>
CEXP std::common_type_t<T, U> lcm(T a, U b) NE {
  using V = std::common_type_t<T, U>;
  using W = to_uint_t<V>;
  if (!a || !b) return 0;
  auto [v, u] = minmax(a = abs(a), b = abs(b));
  return u / (V)gcd_impl_::gcd__<W, W>(u, v) * v;
}

}  // namespace tifa_libs::math

#endif