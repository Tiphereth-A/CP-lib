#ifndef TIFA_LIBS_MATH_IFACT_MOD_GEN
#define TIFA_LIBS_MATH_IFACT_MOD_GEN

#include "../util/util.hpp"

#include "inv_mod_gen.hpp"

namespace tifa_libs::math {

// (i!)^{-1}
inline vec<u64> ifact_mod_gen(size_t sz, u64 mod) {
  assert(sz > 1 && mod >= sz);
  vec<u64> ans = inv_mod_gen(sz, mod);
  for (size_t i = 2; i < sz; ++i) ans[i] = mul_mod_u(ans[i], ans[i - 1], mod);
  return ans;
}

}  // namespace tifa_libs::math

#endif