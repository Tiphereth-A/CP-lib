#ifndef TIFA_LIBS_MATH_DERANGE_MOD_GEN
#define TIFA_LIBS_MATH_DERANGE_MOD_GEN

#include "../math/mul_mod_u.hpp"

namespace tifa_libs::math {

// (derangement) !i for i=0..n-1
inline vec<u64> derange_mod_gen(u32 n, u64 mod) {
  vec<u64> d{0, mod > 1};
  if (n > 2) d.reserve(n);
  else {
    d.resize(n);
    return d;
  }
  for (u32 i = 2; i < n; ++i) d.push_back(mul_mod_u(i, d[i - 1] + d[i - 2], mod));
  return d;
}

}  // namespace tifa_libs::math

#endif