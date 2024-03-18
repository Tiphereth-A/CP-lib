#ifndef TIFALIBS_COMB_GEN_INV
#define TIFALIBS_COMB_GEN_INV

#include "../math/mul_mod_u.hpp"

namespace tifa_libs::math {

// i^{-1} from i=0..n-1
constexpr vec<u64> gen_inv(u32 n, u64 mod) {
  if (n == 0) return {};
  if (n == 1) return {1};
  vec<u64> ans(n);
  ans[0] = ans[1] = 1;
  for (u32 i = 2; i < n; ++i) ans[i] = mul_mod_u(mod - mod / i, ans[mod % i], mod);
  return ans;
}
// i^{-1} from i=0..n-1
template <class mint>
constexpr vec<mint> gen_inv(u32 n) {
  vec<mint> ans(n);
  auto _ = gen_inv(n, mint::mod());
  for (u32 i = 0; i < n; ++i) ans[i] = _[i];
  return ans;
}

}  // namespace tifa_libs::math

#endif