#ifndef TIFA_LIBS_MATH_DERANGE_MOD_GEN
#define TIFA_LIBS_MATH_DERANGE_MOD_GEN

#include "mul_mod_u.hpp"

namespace tifa_libs::math {

// (derangement) !i
inline vec<u64> derange_mod_gen(size_t sz, u64 mod) {
  vec<u64> ans{0, mod > 1};
  if (sz > 2) ans.reserve(sz);
  else {
    ans.resize(sz);
    return ans;
  }
  for (size_t i = 2; i < sz; ++i) ans.push_back(mul_mod_u(i, ans[i - 1] + ans[i - 2], mod));
  return ans;
}

}  // namespace tifa_libs::math

#endif