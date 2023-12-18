#ifndef TIFALIBS_MATH_IS_PROOT_NIMBER
#define TIFALIBS_MATH_IS_PROOT_NIMBER

#include "nimber.hpp"
#include "qpow.hpp"

namespace tifa_libs::math {

template <std::unsigned_integral T, T (*prod)(T, T)>
constexpr bool is_proot_nimber(nimber<T, prod> const& n) {
  if (n == 0) return false;
  for (T p : {3, 5, 17, 257, 641, 65537, 6700417}) {
    if (T(-1) % p) continue;
    if (qpow(n, T(-1) / p) == 1) return false;
  }
  return true;
}

}  // namespace tifa_libs::math

#endif