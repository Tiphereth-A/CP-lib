#ifndef TIFALIBS_COMB_GEN_FACT
#define TIFALIBS_COMB_GEN_FACT

#include "../math/mul_mod.hpp"

namespace tifa_libs::math {

// i! from i=0..n-1
CEXP vecu64 gen_fact(u32 n, u64 mod) {
  if (n <= 1) return vecu64(n, 1);
  vecu64 ans(n);
  ans[0] = ans[1] = 1;
  flt_ (u32, i, 2, n) ans[i] = mul_mod_u(ans[i - 1], i, mod);
  return ans;
}
// i! from i=0..n-1
template <class mint>
CEXP vec<mint> gen_fact(u32 n) {
  vec<mint> ans(n);
  auto _ = gen_fact(n, mint::mod());
  flt_ (u32, i, 0, n) ans[i] = _[i];
  return ans;
}

}  // namespace tifa_libs::math

#endif