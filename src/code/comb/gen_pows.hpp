#ifndef TIFALIBS_COMB_GEN_POWS
#define TIFALIBS_COMB_GEN_POWS

#include "../math/qpow_mod.hpp"

namespace tifa_libs::math {

// i^{b} from i=0..n-1
CEXP vecuu gen_pows(u32 n, u64 b, u64 mod) {
  if (!n) return {};
  vecuu ans(n);
  if (!b) ans[0] = 1;
  if (n == 1) return ans;
  ans[1] = 1;
  flt_ (u32, i, 2, n) ans[i] = qpow_mod(i, b, mod);
  return ans;
}
// i^{b} from i=0..n-1
template <class mint>
CEXP vec<mint> gen_pows(u32 n, u64 b) {
  vec<mint> ans(n);
  auto _ = gen_pows(n, b, mint::mod());
  flt_ (u32, i, 0, n) ans[i] = _[i];
  return ans;
}

}  // namespace tifa_libs::math

#endif