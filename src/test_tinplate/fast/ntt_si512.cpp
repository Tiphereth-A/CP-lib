// original code from https://judge.yosupo.jp/submission/166305
#pragma GCC target("avx512f,bmi")
#include <immintrin.h>
#include <stdint.h>

#include <algorithm>
#include <cassert>
#include <iostream>

using u32 = uint32_t;
using u64 = uint64_t;

namespace simd {
using i512 = __m512i;
using u32x16 = u32 __attribute__((vector_size(64)));
using u64x8 = u64 __attribute__((vector_size(64)));

u32x16 load_u32x16(u32 *ptr) {
  return (u32x16)(_mm512_load_si512((i512 *)ptr));
}
u32x16 loadu_u32x16(u32 *ptr) {
  return (u32x16)(_mm512_loadu_si512((i512 *)ptr));
}
void store_u32x16(u32 *ptr, u32x16 val) {
  _mm512_store_si512((i512 *)ptr, (i512)(val));
}
void storeu_u32x16(u32 *ptr, u32x16 val) {
  _mm512_storeu_si512((i512 *)ptr, (i512)(val));
}

u32x16 set1_u32x16(u32 val) {
  return (u32x16)(_mm512_set1_epi32(val));
}
u64x8 set1_u64x8(u64 val) {
  return (u64x8)(_mm512_set1_epi64(val));
}

u32x16 setr_u32x16_si256(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
  return (u32x16)_mm512_broadcast_i64x4(_mm256_setr_epi32(a0, a1, a2, a3, a4, a5, a6, a7));
}
u64x8 setr_u64x8_si256(u64 a0, u64 a1, u64 a2, u64 a3) {
  return (u64x8)_mm512_broadcast_i64x4(_mm256_setr_epi64x(a0, a1, a2, a3));
}

u64x8 setr_u64x8(u64 a0, u64 a1, u64 a2, u64 a3, u64 a4, u64 a5, u64 a6, u64 a7) {
  return (u64x8)_mm512_setr_epi64(a0, a1, a2, a3, a4, a5, a6, a7);
}

template <int imm8>
u32x16 shuffle_u32x16(u32x16 val) {
  return (u32x16)(_mm512_shuffle_epi32((i512)(val), (_MM_PERM_ENUM)imm8));
}
u32x16 permute_u32x16(u32x16 val, u32x16 p) {
  return (u32x16)(_mm512_permutexvar_epi32((i512)(p), (i512)(val)));
}

template <int imm8>
u32x16 permute_u32x16_epi128(u32x16 a) {
  return (u32x16)(_mm512_shuffle_i64x2((i512)(a), (i512)(a), imm8));
}

template <int imm16>
u32x16 blend_u32x16(u32x16 a, u32x16 b) {
  return (u32x16)(_mm512_mask_blend_epi32(imm16, (i512)(a), (i512)(b)));
}
template <int imm8>
u32x16 blend_u32x16_si256(u32x16 a, u32x16 b) {
  return (u32x16)(_mm512_mask_blend_epi32(imm8 | (imm8 << 8), (i512)(a), (i512)(b)));
}

u32x16 shift_left_u32x16_epi64(u32x16 val, int imm8) {
  return (u32x16)(_mm512_slli_epi64((i512)(val), imm8));
}
u32x16 shift_right_u32x16_epi64(u32x16 val, int imm8) {
  return (u32x16)(_mm512_srli_epi64((i512)(val), imm8));
}

u32x16 min_u32x16(u32x16 a, u32x16 b) {
  return (u32x16)(_mm512_min_epu32((i512)(a), (i512)(b)));
}
u32x16 mul64_u32x16(u32x16 a, u32x16 b) {
  return (u32x16)(_mm512_mul_epu32((i512)(a), (i512)(b)));
}

};  // namespace simd
using namespace simd;

// Montgomery32
struct Montgomery {
  u32 mod;
  u32 mod2;   // 2 * mod
  u32 n_inv;  // n_inv * mod == -1 (mod 2^32)
  u32 r;      // 2^32 % mod
  u32 r2;     // (2^32) ^ 2 % mod

  Montgomery() = default;
  Montgomery(u32 mod) : mod(mod) {
    assert(mod % 2);
    assert(mod < (1 << 30));
    n_inv = 1;
    for (int i = 0; i < 5; i++) {
      n_inv *= 2u + n_inv * mod;
    }
    assert(n_inv * mod == -1u);

    mod2 = 2 * mod;
    r = (1ULL << 32) % mod;
    r2 = r * u64(r) % mod;
  }

  u32 shrink(u32 val) const {
    return std::min(val, val - mod);
  }
  u32 shrink2(u32 val) const {
    return std::min(val, val - mod2);
  }
  u32 shrink_n(u32 val) const {
    return std::min(val, val + mod);
  }
  u32 shrink2_n(u32 val) const {
    return std::min(val, val + mod2);
  }

  // a * b should be in [0, 2**32 * mod)
  // result in [0, 2 * mod)   <false>
  // result in [0, mod)       <true>
  template <bool strict = false>
  u32 mul(u32 a, u32 b) const {
    u64 val = u64(a) * b;
    u32 res = (val + u32(val) * n_inv * u64(mod)) >> 32;
    if constexpr (strict)
      res = shrink(res);
    return res;
  }
};

// Montgomery32
struct Montgomery_simd {
  alignas(64) u32x16 mod;
  alignas(64) u32x16 mod2;   // 2 * mod
  alignas(64) u32x16 n_inv;  // n_inv * mod == -1 (mod 2^32)
  alignas(64) u32x16 r;      // 2^32 % mod
  alignas(64) u32x16 r2;     // (2^32) ^ 2 % mod

  Montgomery_simd() = default;
  Montgomery_simd(u32 md) {
    Montgomery mt(md);
    mod = set1_u32x16(mt.mod);
    mod2 = set1_u32x16(mt.mod2);
    n_inv = set1_u32x16(mt.n_inv);
    r = set1_u32x16(mt.r);
    r2 = set1_u32x16(mt.r2);
  }

  u32x16 shrink(u32x16 val) const {
    return min_u32x16(val, val - mod);
  }
  u32x16 shrink2(u32x16 val) const {
    return min_u32x16(val, val - mod2);
  }
  u32x16 shrink_n(u32x16 val) const {
    return min_u32x16(val, val + mod);
  }
  u32x16 shrink2_n(u32x16 val) const {
    return min_u32x16(val, val + mod2);
  }

  // a * b should be in [0, 2**32 * mod)
  // result in [0, 2 * mod)   <false>
  // result in [0, mod)       <true>
  template <bool strict = false>
  u32x16 mul(u32x16 a, u32x16 b) const {
    u32x16 x0246 = mul64_u32x16(a, b);
    u32x16 x1357 = mul64_u32x16(shift_right_u32x16_epi64(a, 32), shift_right_u32x16_epi64(b, 32));
    u32x16 x0246_ninv = mul64_u32x16(x0246, n_inv);
    u32x16 x1357_ninv = mul64_u32x16(x1357, n_inv);
    u32x16 res = blend_u32x16_si256<0b10'10'10'10>(shift_right_u32x16_epi64(u32x16((u64x8)x0246 + (u64x8)mul64_u32x16(x0246_ninv, mod)), 32),
                                                   u32x16((u64x8)x1357 + (u64x8)mul64_u32x16(x1357_ninv, mod)));
    if constexpr (strict)
      res = shrink(res);
    return res;
  }

  // a * b should be in [0, 2**32 * mod)
  // puts result in high 32-bit of each 64-bit word
  // result in [0, 2 * mod)   <false>
  // result in [0, mod)       <true>
  template <bool strict = false>
  u64x8 mul_to_hi(u64x8 a, u64x8 b) const {
    u32x16 val = mul64_u32x16((u32x16)a, (u32x16)b);
    u32x16 val_ninv = mul64_u32x16(val, n_inv);
    u32x16 res = u32x16(u64x8(val) + u64x8(mul64_u32x16(val_ninv, mod)));
    if constexpr (strict)
      res = shrink(res);
    return (u64x8)res;
  }

  // a * b should be in [0, 2**32 * mod)
  // result in [0, 2 * mod)   <false>
  // result in [0, mod)       <true>
  template <bool strict = false>
  u64x8 mul(u64x8 a, u64x8 b) const {
    return (u64x8)shift_right_u32x16_epi64((u32x16)mul_to_hi<strict>(a, b), 32);
  }
};
#include <array>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

// thanks https://judge.yosupo.jp/submission/142782
struct FFT {
  alignas(64) Montgomery_simd mts;
  Montgomery mt;
  u32 mod, g;

  [[gnu::noinline]] u32 power(u32 base, u32 exp) const {
    const auto mt = this->mt;  // ! to put Montgomery constants in registers
    u32 res = mt.r;
    for (; exp > 0; exp >>= 1) {
      if (exp & 1) {
        res = mt.mul(res, base);
      }
      base = mt.mul(base, base);
    }
    return mt.shrink(res);
  }

  // mod should be prime
  u32 find_pr_root(u32 mod) const {
    u32 m = mod - 1;
    std::vector<u32> vec;
    for (u32 i = 2; u64(i) * i <= m; i++) {
      if (m % i == 0) {
        vec.push_back(i);
        do {
          m /= i;
        } while (m % i == 0);
      }
    }
    if (m != 1) {
      vec.push_back(m);
    }
    for (u32 i = 2;; i++) {
      if (std::all_of(vec.begin(), vec.end(),
                      [&](u32 f) { return mt.r != power(mt.mul(i, mt.r2), (mod - 1) / f); })) {
        return i;
      }
    }
  }

  static constexpr int LG = 30;
  alignas(64) u32 w[8], w_r[8];  // read FFT()

  alignas(64) u64x8 w_cum_x8[LG], w_rcum_x8[LG];     // read FFT()
  alignas(64) u32x16 w_cum_x16[LG], w_rcum_x16[LG];  // read FFT()

  FFT(u32 mod = 998'244'353) : mt(mod), mts(mod), mod(mod) {
    const auto mt = this->mt;  // ! to put Montgomery constants in registers

    g = mt.mul<true>(mt.r2, find_pr_root(mod));

    for (int i = 0; i < LG; i++) {
      u32 f = power(g, u64(mod - 1) >> i + 3);
      u32 res = mt.mul<true>(f, power(power(f, (1 << i + 1) - 2), mod - 2));
      u32 res_r = power(res, mod - 2);
      w_cum_x8[i] = setr_u64x8_si256(res, power(res, 2), res, power(res, 3));
      w_rcum_x8[i] = setr_u64x8_si256(res_r, power(res_r, 2), res_r, power(res_r, 3));
    }
    for (int i = 0; i < LG; i++) {
      u32 f = power(g, u64(mod - 1) >> i + 5);
      f = mt.mul<true>(f, power(power(f, (1 << i + 1) - 2), mod - 2));
      u32 f1 = f;
      u32 f2 = mt.mul<true>(f1, f1);
      u32 f4 = mt.mul<true>(f2, f2);
      u32 f8 = mt.mul<true>(f4, f4);
      w_cum_x16[i] = (u32x16)setr_u32x16_si256(f1, f2, f1, f4, f1, f2, f1, f8);

      u32 f_r = power(f, mod - 2);
      w_rcum_x16[i][0] = mt.r;
      for (int j = 1; j < 16; j++) {
        w_rcum_x16[i][j] = mt.mul<true>(w_rcum_x16[i][j - 1], f_r);
      }
    }

    w[0] = mt.r;
    w_r[0] = mt.r;
    for (int k = 0; k < 3; k++) {
      u32 f = power(g, (mod - 1) >> k + 2);
      u32 f_r = power(f, mod - 2);

      for (int j = 0; j < (1 << k); j++) {
        w[(1 << k) + j] = mt.mul<true>(w[j], f);
        w_r[(1 << k) + j] = mt.mul<true>(w_r[j], f_r);
      }
    }
  }

  // input data[i] in [0, 2 * mod)
  // output data[i] in [0, 4 * mod)
  [[gnu::noinline]] __attribute__((optimize("O3"))) void fft(int lg, u32 *data) const {
    const auto mt = this->mt;    // ! to put Montgomery constants in registers
    const auto mts = this->mts;  // ! to put Montgomery constants in registers

    int n = 1 << lg;
    int k = lg;

    if (lg % 2 == 1) {
      for (int i = 0; i < n / 2; i += 16) {
        u32x16 a = load_u32x16(data + i);
        u32x16 b = load_u32x16(data + n / 2 + i);

        store_u32x16(data + i, mts.shrink2(a + b));
        store_u32x16(data + n / 2 + i, mts.shrink2_n(a - b));
      }
      k--;
    }

    assert(k % 2 == 0);
    for (; k > 4; k -= 2) {
      u64x8 wj_cum = set1_u64x8(mt.r);
      u32x16 w_1 = set1_u32x16(w[1]);
      for (int i = 0; i < n; i += (1 << k)) {
        u32x16 w1 = shuffle_u32x16<0b00'00'00'00>((u32x16)wj_cum);
        u32x16 w2 = permute_u32x16((u32x16)wj_cum, set1_u32x16(2));
        u32x16 w3 = permute_u32x16((u32x16)wj_cum, set1_u32x16(6));
        wj_cum = mts.mul<true>(wj_cum, w_cum_x8[__builtin_ctz(~(i >> k))]);

        for (int j = 0; j < (1 << k - 2); j += 16) {
          u32x16 a = load_u32x16(data + i + 0 * (1 << k - 2) + j);
          u32x16 b = load_u32x16(data + i + 1 * (1 << k - 2) + j);
          u32x16 c = load_u32x16(data + i + 2 * (1 << k - 2) + j);
          u32x16 d = load_u32x16(data + i + 3 * (1 << k - 2) + j);

          a = mts.shrink2(a);
          b = mts.mul(b, w1), c = mts.mul(c, w2), d = mts.mul(d, w3);

          u32x16 a1 = mts.shrink2(a + c), b1 = mts.shrink2(b + d),
                 c1 = mts.shrink2_n(a - c), d1 = mts.mul(b + mts.mod2 - d, w_1);

          store_u32x16(data + i + 0 * (1 << k - 2) + j, a1 + b1);
          store_u32x16(data + i + 1 * (1 << k - 2) + j, a1 + mts.mod2 - b1);
          store_u32x16(data + i + 2 * (1 << k - 2) + j, c1 + d1);
          store_u32x16(data + i + 3 * (1 << k - 2) + j, c1 + mts.mod2 - d1);
        }
      }
    }

    assert(k == 4);
    u32x16 cum = (u32x16)_mm512_setr_epi32(w[0], w[0], w[1], w[0],   // [ w         | w^2       | w * w_1    | w^4       ]
                                           w[2], w[1], w[3], w[0],   // [ w * w_2   | w^2 * w_1 | w * w_3    | w^8       ]
                                           w[4], w[2], w[5], w[1],   // [ w * w_4   | w^2 * w_2 | w * w_5    | w^4 * w_1 ]
                                           w[6], w[3], w[7], w[0]);  // [ w * w_6   | w^2 * w_3 | w * w_7    | w^8       ]
    int n_16 = n / 16;
    for (int i = 0; i < n_16; i++) {
      u32x16 val = load_u32x16(data + i * 16);

      u64x8 w3 = (u64x8)cum;  // no shuffle needed
      u64x8 w2 = (u64x8)shuffle_u32x16<0b00'01'00'01>(cum);
      u64x8 w1 = (u64x8)permute_u32x16(cum, (u32x16)setr_u64x8(3, 3, 3, 3, 11, 11, 11, 11));
      u64x8 w0 = (u64x8)permute_u32x16(cum, (u32x16)setr_u64x8(7, 7, 7, 7, 15, 15, 15, 15));
      cum = mts.mul<true>(cum, w_cum_x16[__builtin_ctz(~i)]);

      u32x16 bw;

      val = mts.shrink2(val);
      bw = permute_u32x16((u32x16)mts.mul_to_hi(w0, (u64x8)permute_u32x16(val, (u32x16)setr_u64x8(8, 9, 10, 11, 12, 13, 14, 15))),
                          (u32x16)setr_u32x16_si256(1, 3, 5, 7, 9, 11, 13, 15));
      val = permute_u32x16_epi128<0b01'00'01'00>(val) + blend_u32x16<0xFF00>(bw, mts.mod2 - bw);

      val = mts.shrink2(val);
      bw = permute_u32x16((u32x16)mts.mul_to_hi(w1, (u64x8)permute_u32x16(val, (u32x16)setr_u64x8(4, 5, 6, 7, 12, 13, 14, 15))),
                          (u32x16)_mm512_setr_epi32(1, 3, 5, 7, 1, 3, 5, 7,
                                                    9, 11, 13, 15, 9, 11, 13, 15));
      val = permute_u32x16_epi128<0b10'10'00'00>(val) + blend_u32x16<0xF0F0>(bw, mts.mod2 - bw);

      val = mts.shrink2(val);
      bw = shuffle_u32x16<0b11'01'11'01>((u32x16)mts.mul_to_hi(w2, (u64x8)shuffle_u32x16<0b00'11'00'10>(val)));
      val = shuffle_u32x16<0b01'00'01'00>(val) + blend_u32x16_si256<0b11'00'11'00>(bw, mts.mod2 - bw);

      val = mts.shrink2(val);
      bw = shuffle_u32x16<0b11'11'01'01>((u32x16)mts.mul_to_hi(w3, (u64x8)shuffle_u32x16<0b00'11'00'01>(val)));
      val = shuffle_u32x16<0b10'10'00'00>(val) + blend_u32x16_si256<0b10'10'10'10>(bw, mts.mod2 - bw);

      store_u32x16(data + i * 16, val);
    }
  }

  // input data[i] in [0, 2 * mod)
  // output data[i] in [0, mod)
  // fc (if specified) should be in [0, mod)
  // if fc is specified everything is multiplied by fc
  [[gnu::noinline]] __attribute__((optimize("O3"))) void ifft(int lg, u32 *data, u32 fc = -1u) const {
    const auto mt = this->mt;    // ! to put Montgomery constants in registers
    const auto mts = this->mts;  // ! to put Montgomery constants in registers

    if (fc == -1u) {
      fc = mt.r;
    }

    int n = 1 << lg;
    int k = 1;

    u32x16 cum2 = (u32x16)_mm512_setr_epi32(w_r[0], w_r[0], w_r[0], w_r[1], w_r[0], w_r[2], w_r[0], w_r[3],
                                            w_r[0], w_r[4], w_r[0], w_r[5], w_r[0], w_r[6], w_r[0], w_r[7]);
    u32x16 cum1 = (u32x16)_mm512_setr_epi32(w_r[0], w_r[0], w_r[0], w_r[0], w_r[0], w_r[0], w_r[1], w_r[1],
                                            w_r[0], w_r[0], w_r[2], w_r[2], w_r[0], w_r[0], w_r[3], w_r[3]);
    u32x16 cum0 = (u32x16)_mm512_setr_epi32(w_r[0], w_r[0], w_r[0], w_r[0], w_r[0], w_r[0], w_r[0], w_r[0],
                                            w_r[0], w_r[0], w_r[0], w_r[0], w_r[1], w_r[1], w_r[1], w_r[1]);
    const u32 inv_2 = mt.mul<true>(mt.r2, (mod + 1) / 2);
    u32x16 cum = set1_u32x16(mt.mul<true>(fc, power(inv_2, lg)));

    int n_16 = n / 16;
    for (int i = 0; i < n_16; i++) {
      u32x16 vec = load_u32x16(data + i * 16);

      vec = mts.mul(cum2, blend_u32x16_si256<0b10'10'10'10>(vec, mts.mod2 - vec) + shuffle_u32x16<0b10'11'00'01>(vec));
      vec = mts.mul(cum1, blend_u32x16_si256<0b11'00'11'00>(vec, mts.mod2 - vec) + shuffle_u32x16<0b01'00'11'10>(vec));
      vec = mts.mul(cum0, blend_u32x16<0xF0F0>(vec, mts.mod2 - vec) + permute_u32x16_epi128<0b10'11'00'01>(vec));
      vec = mts.mul(cum, blend_u32x16<0xFF00>(vec, mts.mod2 - vec) + permute_u32x16_epi128<0b01'00'11'10>(vec));

      store_u32x16(data + i * 16, vec);

      cum = mts.mul<true>(cum, w_rcum_x16[__builtin_ctz(~i)]);
    }
    k += 4;

    assert(k == 5);

    for (; k + 1 <= lg; k += 2) {
      u64x8 wj_cum = set1_u64x8(mt.r);
      u32x16 w_1 = set1_u32x16(w_r[1]);

      for (int i = 0; i < n; i += (1 << k + 1)) {
        u32x16 w1 = shuffle_u32x16<0b00'00'00'00>((u32x16)wj_cum);
        u32x16 w2 = permute_u32x16((u32x16)wj_cum, set1_u32x16(2));
        u32x16 w3 = permute_u32x16((u32x16)wj_cum, set1_u32x16(6));
        wj_cum = mts.mul<true>(wj_cum, w_rcum_x8[__builtin_ctz(~(i >> k + 1))]);

        for (int j = 0; j < (1 << k - 1); j += 16) {
          u32x16 a = load_u32x16(data + i + 0 * (1 << k - 1) + j);
          u32x16 b = load_u32x16(data + i + 1 * (1 << k - 1) + j);
          u32x16 c = load_u32x16(data + i + 2 * (1 << k - 1) + j);
          u32x16 d = load_u32x16(data + i + 3 * (1 << k - 1) + j);

          u32x16 a1 = mts.shrink2(a + b), b1 = mts.shrink2_n(a - b),
                 c1 = mts.shrink2(c + d), d1 = mts.mul(c + mts.mod2 - d, w_1);

          store_u32x16(data + i + 0 * (1 << k - 1) + j, mts.shrink2(a1 + c1));
          store_u32x16(data + i + 1 * (1 << k - 1) + j, mts.mul(w1, b1 + d1));
          store_u32x16(data + i + 2 * (1 << k - 1) + j, mts.mul(w2, a1 + mts.mod2 - c1));
          store_u32x16(data + i + 3 * (1 << k - 1) + j, mts.mul(w3, b1 + mts.mod2 - d1));
        }
      }
    }
    if (k == lg) {
      for (int i = 0; i < n / 2; i += 16) {
        u32x16 a = load_u32x16(data + i);
        u32x16 b = load_u32x16(data + n / 2 + i);

        store_u32x16(data + i, mts.shrink(mts.shrink2(a + b)));
        store_u32x16(data + n / 2 + i, mts.shrink(mts.shrink2_n(a - b)));
      }
    } else {
      assert(k == lg + 1);
      for (int i = 0; i < n; i += 16) {
        u32x16 ai = load_u32x16(data + i);
        store_u32x16(data + i, mts.shrink(ai));
      }
    }
  }

  __attribute__((optimize("O3"))) std::vector<u32>
  convolve_slow(std::vector<u32> a, std::vector<u32> b) const {
    int sz = std::max(0, (int)a.size() + (int)b.size() - 1);
    const auto mt = this->mt;  // ! to put Montgomery constants in registers

    std::vector<u32> c(sz);

    for (int i = 0; i < a.size(); i++) {
      for (int j = 0; j < b.size(); j++) {
        // c[i + j] = (c[i + j] + u64(a[i]) * b[j]) % mod;
        c[i + j] = mt.shrink(c[i + j] + mt.mul<true>(mt.r2, mt.mul(a[i], b[j])));
      }
    }

    return c;
  }

  // a and b should be 64-byte aligned
  // writes (a * b) to a
  __attribute__((optimize("O3"))) [[gnu::noinline]] void convolve(int lg, __restrict__ u32 *a, __restrict__ u32 *b) const {
    if (lg <= 4) {
      int n = (1 << lg);
      __restrict__ u32 *c = (u32 *)_mm_malloc(n * 4, 4);
      memset(c, 0, 4 * n);
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          c[(i + j) & (n - 1)] = mt.shrink2(c[(i + j) & (n - 1)] + mt.mul(a[i], b[j]));
        }
      }
      for (int i = 0; i < n; i++) {
        a[i] = mt.mul<true>(mt.r2, c[i]);
      }
      _mm_free(c);
      return;
    }

    fft(lg, a);
    fft(lg, b);

    const auto mts = this->mts;  // ! to put Montgomery constants in registers
    for (int i = 0; i < (1 << lg); i += 16) {
      u32x16 ai = load_u32x16(a + i), bi = load_u32x16(b + i);
      store_u32x16(a + i, mts.mul(mts.shrink2(ai), mts.shrink2(bi)));
    }

    ifft(lg, a, mt.r2);
  }

  __attribute__((optimize("O3"))) std::vector<u32> convolve(const std::vector<u32> &a, const std::vector<u32> &b) const {
    int sz = std::max(0, (int)a.size() + (int)b.size() - 1);

    int lg = std::__lg(std::max(1, sz - 1)) + 1;
    u32 *ap = (u32 *)_mm_malloc(std::max(64, (1 << lg) * 4), 64);
    u32 *bp = (u32 *)_mm_malloc(std::max(64, (1 << lg) * 4), 64);
    memset(ap, 0, 4 << lg);
    memset(bp, 0, 4 << lg);

    std::copy(a.begin(), a.end(), ap);
    std::copy(b.begin(), b.end(), bp);

    convolve(lg, ap, bp);

    std::vector<u32> res(ap, ap + sz);
    _mm_free(ap);
    _mm_free(bp);
    return res;
  }
};
#include <sys/mman.h>
#include <sys/stat.h>

#include <algorithm>
#include <cstring>
#include <iostream>

using u32 = uint32_t;
using u64 = uint64_t;

// io from https://judge.yosupo.jp/submission/142782

namespace QIO_base {
constexpr int O_buffer_default_size = 1 << 18;
constexpr int O_buffer_default_flush_threshold = 40;
struct _int_to_char_tab {
  char tab[40000];
  constexpr _int_to_char_tab() : tab() {
    for (int i = 0; i != 10000; ++i) {
      for (int j = 3, n = i; ~j; --j) {
        tab[i * 4 + j] = n % 10 + 48, n /= 10;
      }
    }
  }
} constexpr _otab;
}  // namespace QIO_base
namespace QIO_I {
using namespace QIO_base;
struct Qinf {
  FILE *f;
  char *bg, *ed, *p;
  struct stat Fl;
  Qinf(FILE *fi) : f(fi) {
    int fd = fileno(f);
    fstat(fd, &Fl);
    bg = (char *)mmap(0, Fl.st_size + 1, PROT_READ, MAP_PRIVATE, fd, 0);
    p = bg, ed = bg + Fl.st_size;
    madvise(p, Fl.st_size + 1, MADV_SEQUENTIAL);
  }
  ~Qinf() { munmap(bg, Fl.st_size + 1); }
  void skip_space() {
    while (*p <= ' ') {
      ++p;
    }
  }
  char get() { return *p++; }
  char seek() { return *p; }
  bool eof() { return p == ed; }
  Qinf &read(char *s, size_t count) { return memcpy(s, p, count), p += count, *this; }
  Qinf &operator>>(u32 &x) {
    skip_space(), x = 0;
    for (; *p > ' '; ++p) {
      x = x * 10 + (*p & 0xf);
    }
    return *this;
  }
  Qinf &operator>>(int &x) {
    skip_space();
    if (*p == '-') {
      for (++p, x = 48 - *p++; *p > ' '; ++p) {
        x = x * 10 - (*p ^ 48);
      }
    } else {
      for (x = *p++ ^ 48; *p > ' '; ++p) {
        x = x * 10 + (*p ^ 48);
      }
    }
    return *this;
  }
} qin(stdin);
}  // namespace QIO_I
namespace QIO_O {
using namespace QIO_base;
struct Qoutf {
  FILE *f;
  char *bg, *ed, *p;
  char *ed_thre;
  int fp;
  u64 _fpi;
  Qoutf(FILE *fo, size_t sz = O_buffer_default_size) : f(fo), bg(new char[sz]), ed(bg + sz), p(bg), ed_thre(ed - O_buffer_default_flush_threshold), fp(6), _fpi(1000000ull) {}
  void flush() { fwrite_unlocked(bg, 1, p - bg, f), p = bg; }
  void chk() {
    if (__builtin_expect(p > ed_thre, 0)) {
      flush();
    }
  }
  ~Qoutf() {
    flush();
    delete[] bg;
  }
  void put4(u32 x) {
    if (x > 99u) {
      if (x > 999u) {
        memcpy(p, _otab.tab + (x << 2) + 0, 4), p += 4;
      } else {
        memcpy(p, _otab.tab + (x << 2) + 1, 3), p += 3;
      }
    } else {
      if (x > 9u) {
        memcpy(p, _otab.tab + (x << 2) + 2, 2), p += 2;
      } else {
        *p++ = x ^ 48;
      }
    }
  }
  void put2(u32 x) {
    if (x > 9u) {
      memcpy(p, _otab.tab + (x << 2) + 2, 2), p += 2;
    } else {
      *p++ = x ^ 48;
    }
  }
  Qoutf &write(const char *s, size_t count) {
    if (count > 1024 || p + count > ed_thre) {
      flush(), fwrite_unlocked(s, 1, count, f);
    } else {
      memcpy(p, s, count), p += count, chk();
    }
    return *this;
  }
  Qoutf &operator<<(char ch) { return *p++ = ch, *this; }
  Qoutf &operator<<(u32 x) {
    if (x > 99999999u) {
      put2(x / 100000000u), x %= 100000000u;
      memcpy(p, _otab.tab + ((x / 10000u) << 2), 4), p += 4;
      memcpy(p, _otab.tab + ((x % 10000u) << 2), 4), p += 4;
    } else if (x > 9999u) {
      put4(x / 10000u);
      memcpy(p, _otab.tab + ((x % 10000u) << 2), 4), p += 4;
    } else {
      put4(x);
    }
    return chk(), *this;
  }
  Qoutf &operator<<(int x) {
    if (x < 0) {
      *p++ = '-', x = -x;
    }
    return *this << static_cast<u32>(x);
  }
} qout(stdout);
}  // namespace QIO_O
namespace QIO {
using QIO_I::qin;
using QIO_I::Qinf;
using QIO_O::qout;
using QIO_O::Qoutf;
}  // namespace QIO
using namespace QIO;
#include <cassert>
#include <iostream>

int32_t main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  FFT fft(998'244'353);

  int n, m;
  n = m = 5e5;
  qin >> n >> m;

  int lg = std::__lg(std::max(1, n + m - 2)) + 1;

  u32 *a = (u32 *)_mm_malloc(std::max(64, (1 << lg) * 4), 64);
  u32 *b = (u32 *)_mm_malloc(std::max(64, (1 << lg) * 4), 64);

  for (int i = 0; i < n; i++) {
    qin >> a[i];
  }
  memset(a + n, 0, (4 << lg) - 4 * n);
  for (int i = 0; i < m; i++) {
    qin >> b[i];
  }
  memset(b + m, 0, (4 << lg) - 4 * m);

  // for (int i = 0; i < 100; i++)
  //
  {
    fft.convolve(lg, a, b);
  }
  for (int i = 0; i < (n + m - 1); i++) {
    qout << a[i] << " \n"[i + 1 == (n + m - 1)];
  }

  return 0;
}
