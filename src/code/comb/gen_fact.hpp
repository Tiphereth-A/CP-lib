#ifndef TIFA_LIBS_MATH_GEN_FACT
#define TIFA_LIBS_MATH_GEN_FACT

#include "../math/mul_mod_u.hpp"

namespace tifa_libs::math {

// i! from i=0..n-1
inline vec<u64> gen_fact(u32 n, u64 mod) {
  vec<u64> ans(n);
  ans[0] = ans[1] = 1;
  for (u32 i = 2; i < n; ++i) ans[i] = mul_mod_u(ans[i - 1], i, mod);
  return ans;
}
// i! from i=0..n-1
template <class mint>
inline vec<mint> gen_fact(u32 n) {
  vec<mint> ans(n);
  auto _ = gen_fact(n, mint::mod());
  for (u32 i = 0; i < n; ++i) ans[i] = _[i];
  return ans;
}

}  // namespace tifa_libs::math

#endif