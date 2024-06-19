#ifndef TIFALIBS_MATH_NIM_PROD
#define TIFALIBS_MATH_NIM_PROD

#include "../util/util.hpp"

namespace tifa_libs::math {
namespace nim_prod_impl_ {
struct calc8 {
  u16 dp[1 << 8][1 << 8];
  CEXPE calc8() : dp() {
    dp[0][0] = dp[0][1] = dp[1][0] = 0, dp[1][1] = 1;
    fle_ (u32, e, 1, 3) {
      const u32 p = 1 << e, q = p >> 1;
      const u16 ep = u16(1u << p), eq = u16(1u << q);
      flt_ (u16, i, 0, ep)
        flt_ (u16, j, i, ep) {
          if (i < eq && j < eq) continue;
          if (min(i, j) <= 1u) {
            dp[i][j] = dp[j][i] = i * j;
            continue;
          }
          const u16 iu = u16(i >> q), il = u16(i & (eq - 1)), ju = u16(j >> q), jl = u16(j & (eq - 1));
          const u16 u = dp[iu][ju], l = dp[il][jl], ul = dp[iu ^ il][ju ^ jl], uq = dp[u][eq >> 1];
          dp[i][j] = u16((ul ^ l) << q) ^ uq ^ l, dp[j][i] = dp[i][j];
        }
    }
  }
} CEXP c8;

struct calc16 {
  static CEXP u16 proot = 10279;
  static CEXP u32 ppoly = 92191, order = 65535;

  u16 base[16], exp[(1 << 18) + 100];
  u32 log[1 << 16];

 private:
  CEXP u16 d(u32 x) { return u16((x << 1) ^ (x < 32768u ? 0 : ppoly)); }
  CEXP u16 naive(u16 i, u16 j) {
    if (min(i, j) <= 1u) return i * j;
    const u16 q = 8, eq = 1u << 8;
    const u16 iu = u16(i >> q), il = u16(i & (eq - 1)), ju = u16(j >> q), jl = u16(j & (eq - 1));
    const u16 u = c8.dp[iu][ju], l = c8.dp[il][jl], ul = c8.dp[iu ^ il][ju ^ jl], uq = c8.dp[u][eq >> 1];
    return u16((ul ^ l) << q) ^ uq ^ l;
  }

 public:
  CEXPE calc16() : base(), exp(), log() {
    base[0] = 1;
    flt_ (u32, i, 1, 16) base[i] = naive(base[i - 1], proot);
    exp[0] = 1;
    flt_ (u32, i, 1, order) exp[i] = d(exp[i - 1]);
    u16* pre = exp + order + 1;
    pre[0] = 0;
    flt_ (u32, b, 0, 16) {
      const u32 is = 1 << b;
      flt_ (u32, i, is, is * 2) pre[i] = pre[i - is] ^ base[b];
    }
    flt_ (u32, i, 0, order) exp[i] = pre[exp[i]], log[exp[i]] = i;
    const u32 ie_ = 2 * order + 30;
    flt_ (u32, i, order, ie_) exp[i] = exp[i - order];
    for (u32 i = ie_; i < sizeof(exp) / sizeof(u16); ++i) exp[i] = 0;
    log[0] = ie_ + 1;
  }
  CEXP u16 prod(u16 i, u16 j) const { return exp[log[i] + log[j]]; }
  // exp[3] = 2^{15} = 32768
  CEXP u16 Hprod(u16 i, u16 j) const { return exp[log[i] + log[j] + 3]; }
  CEXP u16 H(u16 i) const { return exp[log[i] + 3]; }
  CEXP u16 H2(u16 i) const { return exp[log[i] + 6]; }
} CEXP c16;

CEXP u16 nimprod16(u16 i, u16 j) { return c16.prod(i, j); }
CEXP u32 nimprod32(u32 i, u32 j) {
  const u16 iu = u16(i >> 16), il = u16(i & 65535), ju = u16(j >> 16), jl = u16(j & 65535);
  const u16 l = c16.prod(il, jl), ul = c16.prod(iu ^ il, ju ^ jl), uq = c16.Hprod(iu, ju);
  return (u32(ul ^ l) << 16) ^ uq ^ l;
}

// (+ : xor, x : nim product, * : integer product)
// i x j
// = (iu x ju + il x ju + iu x ji) * 2^{16}
// + (iu x ju x 2^{15}) + il x jl
// (assign ju = 2^{15}, jl = 0)
// = ((iu + il) x 2^{15}) * 2^{16} + (iu x 2^{15} x 2^{15})
CEXP u32 H(u32 i) {
  const u16 iu = u16(i >> 16), il = u16(i & 65535);
  return (u32(c16.H(iu ^ il)) << 16) ^ c16.H2(iu);
}
CEXP u64 nimprod64(u64 i, u64 j) {
  const u32 iu = u32(i >> 32), il = u32(i & u32(-1)), ju = u32(j >> 32), jl = u32(j & u32(-1));
  const u32 l = nimprod32(il, jl), ul = nimprod32(iu ^ il, ju ^ jl), uq = H(nimprod32(iu, ju));
  return (u64(ul ^ l) << 32) ^ uq ^ l;
}
}  // namespace nim_prod_impl_

using nim_prod_impl_::nimprod16, nim_prod_impl_::nimprod32, nim_prod_impl_::nimprod64;

}  // namespace tifa_libs::math

#endif