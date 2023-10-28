#ifndef TIFA_LIBS_MATH_POWS_MOD_GEN
#define TIFA_LIBS_MATH_POWS_MOD_GEN

#include "../math/qpow_mod.hpp"

namespace tifa_libs::math {

// i^{n} from 0 to m
inline vec<u64> pows_mod_gen(u64 sz, u64 n, u64 mod) {
  vec<u64> ans(sz);
  if (!sz) return {};
  if (!n) ans[0] = 1;
  if (sz == 1) return ans;
  ans[1] = 1;
  for (usz i = 2; i < sz; ++i) ans[i] = qpow_mod(i, n, mod);
  return ans;
}

}  // namespace tifa_libs::math

#endif