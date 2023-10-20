#ifndef TIFA_LIBS_MATH_DERANGE_MOD_GEN
#define TIFA_LIBS_MATH_DERANGE_MOD_GEN

#include "../math/mul_mod_u.hpp"

namespace tifa_libs::math {

// (derangement) !i
inline vec<u64> derange_mod_gen(usz sz, u64 mod) {
  vec<u64> d{0, mod > 1};
  if (sz > 2) d.reserve(sz);
  else {
    d.resize(sz);
    return d;
  }
  for (usz i = 2; i < sz; ++i) d.push_back(mul_mod_u(i, d[i - 1] + d[i - 2], mod));
  return d;
}

}  // namespace tifa_libs::math

#endif