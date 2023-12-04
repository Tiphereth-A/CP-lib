#ifndef TIFALIBS_MATH_NIM_PROD
#define TIFALIBS_MATH_NIM_PROD

#include "../util/util.hpp"

namespace tifa_libs::math {

namespace nim_prod_impl_ {

struct calc8 {
  u16 dp[1 << 8][1 << 8];
  explicit constexpr calc8() : dp() {
    dp[0][0] = dp[0][1] = dp[1][0] = 0;
    dp[1][1] = 1;
    for (u32 e = 1; e <= 3; ++e) {
      u32 p = 1 << e, q = p >> 1;
      u16 ep = u16(1u << p), eq = u16(1u << q);
      for (u16 i = 0; i < ep; ++i)
        for (u16 j = i; j < ep; ++j) {
          if (i < eq && j < eq) continue;
          if (std::min(i, j) <= 1u) {
            dp[i][j] = dp[j][i] = i * j;
            continue;
          }
          u16 iu = u16(i >> q), il = u16(i & (eq - 1));
          u16 ju = u16(j >> q), jl = u16(j & (eq - 1));
          u16 u = dp[iu][ju], l = dp[il][jl];
          u16 ul = dp[iu ^ il][ju ^ jl], uq = dp[u][eq >> 1];
          dp[i][j] = u16((ul ^ l) << q) ^ uq ^ l;
          dp[j][i] = dp[i][j];
        }
    }
  }
} constexpr c8;

struct calc16 {
  static constexpr u16 proot = 10279;
  static constexpr u32 ppoly = 92191, order = 65535;

  u16 base[16], exp[(1 << 18) + 100];
  u32 log[1 << 16];

 private:
  constexpr u16 d(u32 x) { return u16((x << 1) ^ (x < 32768u ? 0 : ppoly)); }

  constexpr u16 naive(u16 i, u16 j) {
    if (std::min(i, j) <= 1u) return i * j;
    u16 q = 8, eq = 1u << 8;
    u16 iu = u16(i >> q), il = u16(i & (eq - 1));
    u16 ju = u16(j >> q), jl = u16(j & (eq - 1));
    u16 u = c8.dp[iu][ju], l = c8.dp[il][jl];
    u16 ul = c8.dp[iu ^ il][ju ^ jl], uq = c8.dp[u][eq >> 1];
    return u16((ul ^ l) << q) ^ uq ^ l;
  }

 public:
  explicit constexpr calc16() : base(), exp(), log() {
    base[0] = 1;
    for (u32 i = 1; i < 16; ++i) base[i] = naive(base[i - 1], proot);
    exp[0] = 1;
    for (u32 i = 1; i < order; ++i) exp[i] = d(exp[i - 1]);
    u16* pre = exp + order + 1;
    pre[0] = 0;
    for (u32 b = 0; b < 16; b++) {
      u32 is = 1 << b, ie = is << 1;
      for (u32 i = is; i < ie; ++i) pre[i] = pre[i - is] ^ base[b];
    }
    for (u32 i = 0; i < order; ++i) exp[i] = pre[exp[i]], log[exp[i]] = i;

    u32 ie = 2 * order + 30;
    for (u32 i = order; i < ie; ++i) exp[i] = exp[i - order];
    for (u32 i = ie; i < sizeof(exp) / sizeof(u16); ++i) exp[i] = 0;
    log[0] = ie + 1;
  }

  constexpr u16 prod(u16 i, u16 j) const { return exp[log[i] + log[j]]; }

  // exp[3] = 2^{15} = 32768
  constexpr u16 Hprod(u16 i, u16 j) const { return exp[log[i] + log[j] + 3]; }
  constexpr u16 H(u16 i) const { return exp[log[i] + 3]; }
  constexpr u16 H2(u16 i) const { return exp[log[i] + 6]; }
} constexpr c16;

constexpr u16 nimprod16(u16 i, u16 j) { return c16.prod(i, j); }

constexpr u32 nimprod32(u32 i, u32 j) {
  u16 iu = u16(i >> 16), il = u16(i & 65535);
  u16 ju = u16(j >> 16), jl = u16(j & 65535);
  u16 l = c16.prod(il, jl), ul = c16.prod(iu ^ il, ju ^ jl), uq = c16.Hprod(iu, ju);
  return (u32(ul ^ l) << 16) ^ uq ^ l;
}

// (+ : xor, x : nim product, * : integer product)
// i x j
// = (iu x ju + il x ju + iu x ji) * 2^{16}
// + (iu x ju x 2^{15}) + il x jl
// (assign ju = 2^{15}, jl = 0)
// = ((iu + il) x 2^{15}) * 2^{16} + (iu x 2^{15} x 2^{15})
constexpr u32 H(u32 i) {
  u16 iu = u16(i >> 16), il = u16(i & 65535);
  return (u32(c16.H(iu ^ il)) << 16) ^ c16.H2(iu);
}

constexpr u64 nimprod64(u64 i, u64 j) {
  u32 iu = u32(i >> 32), il = u32(i & u32(-1));
  u32 ju = u32(j >> 32), jl = u32(j & u32(-1));
  u32 l = nimprod32(il, jl), ul = nimprod32(iu ^ il, ju ^ jl), uq = H(nimprod32(iu, ju));
  return (u64(ul ^ l) << 32) ^ uq ^ l;
}
}  // namespace nim_prod_impl_

using nim_prod_impl_::nimprod16, nim_prod_impl_::nimprod32, nim_prod_impl_::nimprod64;

}  // namespace tifa_libs::math

#endif