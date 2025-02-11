#ifndef TIFALIBS_COMB_GEN_IPOWI
#define TIFALIBS_COMB_GEN_IPOWI

#include "../math/isqrt.hpp"
#include "../math/qpow_mod.hpp"
#include "../nt/lsieve.hpp"

namespace tifa_libs::math {
namespace gen_ipowi_impl_ {
struct ls_ipowi {
  static inline u64 mod;
  vecuu ipowi;

 protected:
  const u32 B;
  vvecuu fp, fpb;
  u32 pre_j, gap;
  u64 now_r;
  arr<u64, 355> p{1};  // maximal prime gaps: g_n=354 => p_n=4,302,407,359

  CEXPE ls_ipowi(u32 n) NE : ipowi(n), B{isqrt(n)}, fp(B + 1, vecuu(B + 1)), fpb(B + 1, vecuu(B + 1)), pre_j{0}, gap{0}, now_r{1} {
    if (n) ipowi[0] = 1;
    if (n > 1) ipowi[1] = 1;
  }
  void prime(u32 p) NE {
    if (ipowi[p] = qpow_mod(p, p, mod); p <= B) {
      fp[p][0] = 1;
      flt_ (u32, j, 1, B + 1)
        fp[p][j] = mul_mod_u(fp[p][j - 1], ipowi[p], mod);
      fpb[p][0] = 1;
      flt_ (u32, j, 1, B + 1)
        fpb[p][j] = mul_mod_u(fpb[p][j - 1], fp[p].back(), mod);
    }
  }
  void coprime(u32 i, u32 j) NE {
    if (j <= pre_j) now_r = 1, pre_j = gap = 0;
    if (u32 new_gap = j - pre_j; new_gap > gap) {
      flt_ (u32, x, gap + 1, new_gap + 1) p[x] = mul_mod_u(p[x - 1], ipowi[i], mod);
      gap = new_gap;
    }
    now_r = mul_mod_u(now_r, p[j - pre_j], mod);
    ipowi[i * j] = mul_mod_u(mul_mod_u(fp[j][i % B], fpb[j][i / B], mod), now_r, mod);
    pre_j = j;
  }
  void not_coprime(u32 i, u32 j) NE { coprime(i, j); }
};
}  // namespace gen_ipowi_impl_

// i^i from i=0..n-1
CEXP vecuu gen_ipowi(u32 n, u64 mod) NE {
  if (n < 2) return vecuu(n, 1);
  gen_ipowi_impl_::ls_ipowi::mod = mod;
  return lsieve<gen_ipowi_impl_::ls_ipowi>(n).ipowi;
}
// i^i from i=0..n-1
template <class mint>
CEXP vec<mint> gen_ipowi(u32 n) NE {
  vec<mint> ans(n);
  auto _ = gen_ipowi(n, mint::mod());
  flt_ (u32, i, 0, n) ans[i] = _[i];
  return ans;
}

}  // namespace tifa_libs::math

#endif