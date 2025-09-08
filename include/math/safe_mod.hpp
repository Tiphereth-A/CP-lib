#ifndef TIFALIBS_MATH_SAFE_MOD
#define TIFALIBS_MATH_SAFE_MOD

#include "../util/traits_math.hpp"

namespace tifa_libs::math {

template <int_c T>
CEXP T safe_mod(T x, to_uint_t<T> mod) NE {
  if CEXP (sint_c<T>) {
    if (x <= -(T)mod || x >= (T)mod) x %= (T)mod;
    retif_((x < 0), x + (T)mod, x);
  } else {
    retif_((x >= mod), x % mod, x);
  }
}

}  // namespace tifa_libs::math

#endif