#ifndef TIFA_LIBS_MATH_FACT_MOD_GEN
#define TIFA_LIBS_MATH_FACT_MOD_GEN

#include "../math/mul_mod_u.hpp"

namespace tifa_libs::math {

// i! from i=0..n-1
inline vec<u64> fact_mod_gen(u32 n, u64 mod) {
  vec<u64> ans(n);
  ans[0] = ans[1] = 1;
  for (u32 i = 2; i < n; ++i) ans[i] = mul_mod_u(ans[i - 1], i, mod);
  return ans;
}

}  // namespace tifa_libs::math

#endif