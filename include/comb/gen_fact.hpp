#ifndef TIFALIBS_COMB_GEN_FACT
#define TIFALIBS_COMB_GEN_FACT

#include "../math/mul_mod.hpp"
#include "../util/alias_others.hpp"

namespace tifa_libs::math {

// i! from i=0..n-1
CEXP vecuu gen_fact(u32 n, u64 mod) NE {
  retif_((n <= 1) [[unlikely]], vecuu(n, 1));
  vecuu ans(n);
  ans[0] = ans[1] = 1;
  flt_ (u32, i, 2, n) ans[i] = mul_mod_u(ans[i - 1], i, mod);
  return ans;
}
// i! from i=0..n-1
template <class mint>
CEXP vec<mint> gen_fact(u32 n) NE {
  vec<mint> ans(n);
  auto _ = gen_fact(n, mint::mod());
  flt_ (u32, i, 0, n) ans[i] = _[i];
  return ans;
}

}  // namespace tifa_libs::math

#endif