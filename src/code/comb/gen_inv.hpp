#ifndef TIFALIBS_COMB_GEN_INV
#define TIFALIBS_COMB_GEN_INV

#include "../math/mul_mod.hpp"

namespace tifa_libs::math {

// i^{-1} from i=0..n-1
CEXP vecuu gen_inv(u32 n, u64 mod) NE {
  if (n <= 1) return vecuu(n, 1);
  vecuu ans(n);
  ans[0] = ans[1] = 1;
  flt_ (u32, i, 2, n) ans[i] = mul_mod_u(mod - mod / i, ans[mod % i], mod);
  return ans;
}
// i^{-1} from i=0..n-1
template <class mint>
CEXP vec<mint> gen_inv(u32 n) NE {
  vec<mint> ans(n);
  auto _ = gen_inv(n, mint::mod());
  flt_ (u32, i, 0, n) ans[i] = _[i];
  return ans;
}

}  // namespace tifa_libs::math

#endif