#ifndef TIFALIBS_NT_GL_GCD_LIB
#define TIFALIBS_NT_GL_GCD_LIB

#include "../../../util/traits/math/lib.hpp"

namespace tifa_libs::math {

namespace gcd_impl_ {
template <uint_c T, uint_c U>
CEXP std::common_type_t<T, U> gcd__(T u, U v) NE {
  using W = std::common_type_t<T, U>;
  retif_((!u || !v) [[unlikely]], u ^ v);
  const auto k = std::__countr_zero(u | v);
  u >>= k, v >>= k;
  do {
    if (W _ = v >> std::__countr_zero(v); u > _) v = u - _, u = _;
    else v = _ - u;
  } while (v);
  return u << k;
}
}  // namespace gcd_impl_

template <int_c T, int_c U>
CEXP auto gcd(T a, U b) NE { return gcd_impl_::gcd__((to_uint_t<T>)abs(a), (to_uint_t<U>)abs(b)); }

}  // namespace tifa_libs::math

#endif