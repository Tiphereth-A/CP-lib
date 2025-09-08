#ifndef TIFALIBS_MATH_IS_PROOT_NIMBER
#define TIFALIBS_MATH_IS_PROOT_NIMBER

#include "../math/nimber.hpp"
#include "../math/qpow.hpp"

namespace tifa_libs::math {

template <std::unsigned_integral T, T (*prod)(T, T)>
CEXP bool is_proot_nimber(nimber<T, prod> CR n) NE {
  retif_((n == 0) [[unlikely]], false);
  for (T p : {3, 5, 17, 257, 641, 65537, 6700417}) {
    if (T(-1) % p) continue;
    if (qpow(n, T(-1) / p) == 1) return false;
  }
  return true;
}

}  // namespace tifa_libs::math

#endif