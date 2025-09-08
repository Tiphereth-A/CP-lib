#ifndef TIFALIBS_COMB_GEN_POWS
#define TIFALIBS_COMB_GEN_POWS

#include "../math/qpow_mod.hpp"
#include "../nt/lsieve.hpp"

namespace tifa_libs::math {
namespace gen_pows_impl_ {
struct ls_pows {
  static inline u64 b, mod;
  vecuu pows;

 protected:
  CEXPE ls_pows(u32 n) NE : pows(n) {
    if (n > 1) pows[1] = 1;
  }
  void prime(u32 p) NE { pows[p] = qpow_mod(p, b, mod); }
  void coprime(u32 i, u32 j) NE { pows[i * j] = mul_mod_u(pows[i], pows[j], mod); }
  void not_coprime(u32 i, u32 j) NE { coprime(i, j); }
};
}  // namespace gen_pows_impl_

// i^{b} from i=0..n-1
CEXP vecuu gen_pows(u32 n, u64 b, u64 mod) NE {
  retif_((!b) [[unlikely]], vecuu(n, mod > 1));
  retif_((!n) [[unlikely]], {});
  gen_pows_impl_::ls_pows::b = b;
  gen_pows_impl_::ls_pows::mod = mod;
  return lsieve<gen_pows_impl_::ls_pows>(n).pows;
}
// i^{b} from i=0..n-1
template <class mint>
CEXP vec<mint> gen_pows(u32 n, u64 b) NE {
  vec<mint> ans(n);
  auto _ = gen_pows(n, b, mint::mod());
  flt_ (u32, i, 0, n) ans[i] = _[i];
  return ans;
}

}  // namespace tifa_libs::math

#endif