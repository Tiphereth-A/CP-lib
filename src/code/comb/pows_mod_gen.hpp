#ifndef TIFA_LIBS_MATH_POWS_MOD_GEN
#define TIFA_LIBS_MATH_POWS_MOD_GEN

#include "../math/qpow_mod.hpp"

namespace tifa_libs::math {

// i^{b} from i=0..n-1
inline vec<u64> pows_mod_gen(u32 n, u64 b, u64 mod) {
  vec<u64> ans(n);
  if (!n) return {};
  if (!b) ans[0] = 1;
  if (n == 1) return ans;
  ans[1] = 1;
  for (u32 i = 2; i < n; ++i) ans[i] = qpow_mod(i, b, mod);
  return ans;
}

}  // namespace tifa_libs::math

#endif