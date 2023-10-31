#ifndef TIFA_LIBS_MATH_GEN_INVSEQ
#define TIFA_LIBS_MATH_GEN_INVSEQ

#include "../math/inverse.hpp"
#include "../math/mul_mod_u.hpp"

namespace tifa_libs::math {

// i^{-1} for i in v
inline vec<u64> gen_invseq(vec<u64> const &v, u64 mod) {
  usz n = v.size();
  vec<u64> ans(n);
  ans[0] = v[1];
  for (usz i = 1; i < n; ++i) ans[i] = mul_mod_u(ans[i - 1], v[i], mod);
  u64 _ = inverse(ans.back(), mod);
  for (usz i = n - 1; i; --i) {
    ans[i] = mul_mod_u(_, ans[i - 1], mod);
    _ = mul_mod_u(_, v[i], mod);
  }
  ans[0] = _;
  return ans;
}
// i^{-1} for i in v
template <class mint>
inline vec<mint> gen_invseq(vec<mint> const &v) {
  usz n = v.size();
  vec<mint> ans(n);
  auto _ = gen_invseq(v, mint::mod());
  for (u32 i = 0; i < n; ++i) ans[i] = _[i];
  return ans;
}

}  // namespace tifa_libs::math

#endif