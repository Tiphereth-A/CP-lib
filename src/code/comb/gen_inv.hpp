#ifndef TIFA_LIBS_MATH_GEN_INV
#define TIFA_LIBS_MATH_GEN_INV

#include "../math/mul_mod_u.hpp"

namespace tifa_libs::math {

// i^{-1} from i=0..n-1
inline vec<u64> gen_inv(u32 n, u64 mod) {
  vec<u64> ans(n);
  ans[0] = ans[1] = 1;
  for (u32 i = 2; i < n; ++i) ans[i] = mul_mod_u(mod - mod / i, ans[mod % i], mod);
  return ans;
}

}  // namespace tifa_libs::math

#endif