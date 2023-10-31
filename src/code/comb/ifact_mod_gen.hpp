#ifndef TIFA_LIBS_MATH_IFACT_MOD_GEN
#define TIFA_LIBS_MATH_IFACT_MOD_GEN

#include "inv_mod_gen.hpp"

namespace tifa_libs::math {

// (i!)^{-1} from i=0..n-1
inline vec<u64> ifact_mod_gen(u32 n, u64 mod, vec<u64> inv) {
  for (u32 i = 2; i < n; ++i) inv[i] = mul_mod_u(inv[i], inv[i - 1], mod);
  return inv;
}
// (i!)^{-1} from i=0..n-1
inline vec<u64> ifact_mod_gen(u32 n, u64 mod) { return ifact_mod_gen(n, mod, inv_mod_gen(n, mod)); }

}  // namespace tifa_libs::math

#endif