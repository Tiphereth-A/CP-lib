#ifndef TIFALIBS_MATH_IS_PROOT_NIMBER
#define TIFALIBS_MATH_IS_PROOT_NIMBER

#include "nimber.hpp"
#include "qpow.hpp"

namespace tifa_libs::math {

template <class uint, uint (*prod)(uint, uint)>
constexpr bool is_proot_nimber(nimber<uint, prod> const& n) {
  if (n == 0) return false;
  for (uint p : {3, 5, 17, 257, 641, 65537, 6700417}) {
    if (uint(-1) % p) continue;
    if (qpow(n, uint(-1) / p) == 1) return false;
  }
  return true;
}

}  // namespace tifa_libs::math

#endif