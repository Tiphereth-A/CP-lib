#ifndef TIFA_LIBS_MATH_INV_MOD_GEN
#define TIFA_LIBS_MATH_INV_MOD_GEN

#include "mul_mod_u.hpp"

namespace tifa_libs::math {

// i^{-1}
inline vec<u64> inv_mod_gen(size_t sz, u64 mod) {
  assert(sz > 1 && mod >= sz);
  vec<u64> ans(sz, 1);
  for (size_t i = 2; i < sz; ++i) ans[i] = mul_mod_u(mod - mod / i, ans[mod % i], mod);
  return ans;
}

}  // namespace tifa_libs::math

#endif