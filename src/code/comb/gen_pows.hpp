#ifndef TIFALIBS_COMB_GEN_POWS
#define TIFALIBS_COMB_GEN_POWS

#include "../math/qpow_mod.hpp"

namespace tifa_libs::math {

// i^{b} from i=0..n-1
inline vec<u64> gen_pows(u32 n, u64 b, u64 mod) {
  vec<u64> ans(n);
  if (!n) return {};
  if (!b) ans[0] = 1;
  if (n == 1) return ans;
  ans[1] = 1;
  for (u32 i = 2; i < n; ++i) ans[i] = qpow_mod(i, b, mod);
  return ans;
}
// i^{b} from i=0..n-1
template <class mint>
vec<mint> gen_pows(u32 n, u64 b) {
  vec<mint> ans(n);
  auto _ = gen_pows(n, b, mint::mod());
  for (u32 i = 0; i < n; ++i) ans[i] = _[i];
  return ans;
}

}  // namespace tifa_libs::math

#endif