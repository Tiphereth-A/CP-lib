#ifndef TIFALIBS_COMB_GEN_INVSEQ
#define TIFALIBS_COMB_GEN_INVSEQ

#include "../math/mul_mod_u.hpp"
#include "../nt/inverse.hpp"

namespace tifa_libs::math {

// i^{-1} for i in v
constexpr vec<u64> gen_invseq(vec<u64> const &v, u64 mod) {
  u32 n = (u32)v.size();
  if (n == 0) return {};
  if (n == 1) return {inverse(v[0], mod)};
  vec<u64> ans(n);
  ans[0] = v[1];
  for (u32 i = 1; i < n; ++i) ans[i] = mul_mod_u(ans[i - 1], v[i], mod);
  u64 _ = inverse(ans.back(), mod);
  for (u32 i = n - 1; i; --i) {
    ans[i] = mul_mod_u(_, ans[i - 1], mod);
    _ = mul_mod_u(_, v[i], mod);
  }
  ans[0] = _;
  return ans;
}
// i^{-1} for i in v
template <class mint>
constexpr vec<mint> gen_invseq(vec<mint> const &v) {
  u32 n = (u32)v.size();
  vec<mint> ans(n);
  auto _ = gen_invseq(v, mint::mod());
  for (u32 i = 0; i < n; ++i) ans[i] = _[i];
  return ans;
}

}  // namespace tifa_libs::math

#endif