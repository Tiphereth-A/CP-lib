#ifndef TIFA_LIBS_MATH_IFACT_MOD_GEN
#define TIFA_LIBS_MATH_IFACT_MOD_GEN

#include "inv_mod_gen.hpp"

namespace tifa_libs::math {

// (i!)^{-1}
inline vec<u64> ifact_mod_gen(size_t sz, u64 mod, vec<u64> const& inv) {
  vec<u64> ans = inv;
  for (size_t i = 2; i < sz; ++i) ans[i] = mul_mod_u(ans[i], ans[i - 1], mod);
  return ans;
}
// (i!)^{-1}
inline vec<u64> ifact_mod_gen(size_t sz, u64 mod) { return ifact_mod_gen(sz, mod, inv_mod_gen(sz, mod)); }

}  // namespace tifa_libs::math

#endif