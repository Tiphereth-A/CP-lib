#ifndef TIFA_LIBS_FAST_MONTGOMERY_SI512
#define TIFA_LIBS_FAST_MONTGOMERY_SI512

// clang-format off
#include "../util/si_avx512.hpp"
#include "../math/montgomery.hpp"
// clang-format on

namespace tifa_libs::math {

struct Montgomery_si512 {
  alignas(64) u32x16 mod;
  alignas(64) u32x16 mod2;   // 2 * mod
  alignas(64) u32x16 n_inv;  // n_inv * mod == -1 (mod 2^32)
  alignas(64) u32x16 r;      // 2^32 % mod
  alignas(64) u32x16 r2;     // (2^32) ^ 2 % mod

  Montgomery_si512() = default;
  Montgomery_si512(u32 md) {
    Montgomery mt(md);
    mod = set1_u32x16(mt.mod);
    mod2 = set1_u32x16(mt.mod2);
    n_inv = set1_u32x16(mt.n_inv);
    r = set1_u32x16(mt.r);
    r2 = set1_u32x16(mt.r2);
  }

  u32x16 shrink(u32x16 val) const { return min_u32x16(val, val - mod); }
  u32x16 shrink2(u32x16 val) const { return min_u32x16(val, val - mod2); }
  u32x16 shrink_n(u32x16 val) const { return min_u32x16(val, val + mod); }
  u32x16 shrink2_n(u32x16 val) const { return min_u32x16(val, val + mod2); }

  // a * b should be in [0, 2**32 * mod)
  // result in [0, 2 * mod)   <false>
  // result in [0, mod)       <true>
  template <bool strict = false>
  u32x16 mul(u32x16 a, u32x16 b) const {
    u32x16 x0246 = mul64_u32x16(a, b);
    u32x16 x1357 = mul64_u32x16(shift_right_u32x16_epi64(a, 32), shift_right_u32x16_epi64(b, 32));
    u32x16 x0246_ninv = mul64_u32x16(x0246, n_inv), x1357_ninv = mul64_u32x16(x1357, n_inv);
    u32x16 res = blend_u32x16_si256<0b10'10'10'10>(shift_right_u32x16_epi64(u32x16((u64x8)x0246 + (u64x8)mul64_u32x16(x0246_ninv, mod)), 32), u32x16((u64x8)x1357 + (u64x8)mul64_u32x16(x1357_ninv, mod)));
    if constexpr (strict) res = shrink(res);
    return res;
  }

  // a * b should be in [0, 2**32 * mod)
  // puts result in high 32-bit of each 64-bit word
  // result in [0, 2 * mod)   <false>
  // result in [0, mod)       <true>
  template <bool strict = false>
  u64x8 mul_to_hi(u64x8 a, u64x8 b) const {
    u32x16 val = mul64_u32x16((u32x16)a, (u32x16)b), val_ninv = mul64_u32x16(val, n_inv);
    u32x16 res = u32x16(u64x8(val) + u64x8(mul64_u32x16(val_ninv, mod)));
    if constexpr (strict) res = shrink(res);
    return (u64x8)res;
  }

  // a * b should be in [0, 2**32 * mod)
  // result in [0, 2 * mod)   <false>
  // result in [0, mod)       <true>
  template <bool strict = false>
  u64x8 mul(u64x8 a, u64x8 b) const { return (u64x8)shift_right_u32x16_epi64((u32x16)mul_to_hi<strict>(a, b), 32); }
};

}  // namespace tifa_libs::math

#endif