#ifndef TIFALIBS_NT_GL_INV_GCD_LIB
#define TIFALIBS_NT_GL_INV_GCD_LIB

#include "../../../math/safe_mod/lib.hpp"
#include "../../../util/alias/others/lib.hpp"
#include "../exgcd/lib.hpp"

namespace tifa_libs::math {

template <uint_c T>
CEXP ptt<T> inv_gcd(T n, T mod) NE {
  using U = to_sint_t<T>;
  auto [g, x] = exgcd<U, true>(U(n % mod), (U)mod);
  return {g, safe_mod(x, mod)};
}

}  // namespace tifa_libs::math

#endif