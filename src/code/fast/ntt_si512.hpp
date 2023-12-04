#ifndef TIFALIBS_FAST_NTT_SI512
#define TIFALIBS_FAST_NTT_SI512

// clang-format off
#include "montgomery_si512.hpp"
#include "../math/proot_u32.hpp"
// clang-format on

namespace tifa_libs::math {

// from <https://judge.yosupo.jp/submission/166305>
struct NTT_si512 {
  // avoid weird CE from clang
  using pu32 = u32 *;

  alignas(64) Montgomery_si512 mts;
  Montgomery mt;
  u32 mod, g;

  [[gnu::noinline]] u32 power(u32 base, u32 exp) const {
    const auto mt = this->mt;  // ! to put Montgomery constants in registers
    u32 res = mt.r;
    for (; exp > 0; exp >>= 1) {
      if (exp & 1) res = mt.mul(res, base);
      base = mt.mul(base, base);
    }
    return mt.shrink(res);
  }
  static constexpr int LG = 30;
  alignas(64) u32 w[8], w_r[8];                      // read NTT()
  alignas(64) u64x8 w_cum_x8[LG], w_rcum_x8[LG];     // read NTT()
  alignas(64) u32x16 w_cum_x16[LG], w_rcum_x16[LG];  // read NTT()
  explicit NTT_si512(u32 mod = 998244353) : mts(mod), mt(mod), mod(mod) {
    const auto mt = this->mt;  // ! to put Montgomery constants in registers
    g = mt.mul<true>(mt.r2, proot_u32(mod));
    for (int i = 0; i < LG; ++i) {
      u32 f = power(g, u32(u64(mod - 1) >> (i + 3)));
      u32 res = mt.mul<true>(f, power(power(f, (1 << (i + 1)) - 2), mod - 2));
      u32 res_r = power(res, mod - 2);
      w_cum_x8[i] = setr_u64x8_si256(res, power(res, 2), res, power(res, 3));
      w_rcum_x8[i] = setr_u64x8_si256(res_r, power(res_r, 2), res_r, power(res_r, 3));
    }
    for (int i = 0; i < LG; ++i) {
      u32 f = power(g, u32(u64(mod - 1) >> (i + 5)));
      f = mt.mul<true>(f, power(power(f, (1 << (i + 1)) - 2), mod - 2));
      u32 f1 = f;
      u32 f2 = mt.mul<true>(f1, f1);
      u32 f4 = mt.mul<true>(f2, f2);
      u32 f8 = mt.mul<true>(f4, f4);
      w_cum_x16[i] = (u32x16)setr_u32x16_si256(f1, f2, f1, f4, f1, f2, f1, f8);
      u32 f_r = power(f, mod - 2);
      w_rcum_x16[i][0] = mt.r;
      for (int j = 1; j < 16; ++j) w_rcum_x16[i][j] = mt.mul<true>(w_rcum_x16[i][j - 1], f_r);
    }
    w[0] = mt.r;
    w_r[0] = mt.r;
    for (int k = 0; k < 3; k++) {
      u32 f = power(g, (mod - 1) >> (k + 2)), f_r = power(f, mod - 2);
      for (int j = 0; j < (1 << k); ++j) {
        w[(1 << k) + j] = mt.mul<true>(w[j], f);
        w_r[(1 << k) + j] = mt.mul<true>(w_r[j], f_r);
      }
    }
  }
  // input data[i] in [0, 2 * mod)
  // output data[i] in [0, 4 * mod)
  [[gnu::noinline]] __attribute__((optimize("O3"))) void fft(u32 lg, u32 *data) const {
    const auto mt = this->mt;    // ! to put Montgomery constants in registers
    const auto mts = this->mts;  // ! to put Montgomery constants in registers
    u32 n = 1 << lg, k = lg;
    if (lg % 2 == 1) {
      for (u32 i = 0; i < n / 2; i += 16) {
        u32x16 a = load_u32x16(data + i), b = load_u32x16(data + n / 2 + i);
        store_u32x16(data + i, mts.shrink2(a + b));
        store_u32x16(data + n / 2 + i, mts.shrink2_n(a - b));
      }
      k--;
    }
    assert(k % 2 == 0);
    for (; k > 4; k -= 2) {
      u64x8 wj_cum = set1_u64x8(mt.r);
      u32x16 w_1 = set1_u32x16(w[1]);
      for (u32 i = 0; i < n; i += (1 << k)) {
        u32x16 w1 = shuffle_u32x16<0b00'00'00'00>((u32x16)wj_cum);
        u32x16 w2 = permute_u32x16((u32x16)wj_cum, set1_u32x16(2));
        u32x16 w3 = permute_u32x16((u32x16)wj_cum, set1_u32x16(6));
        wj_cum = mts.mul<true>(wj_cum, w_cum_x8[__builtin_ctz(~(i >> k))]);
        for (u32 j = 0; j < (1 << (k - 2)); j += 16) {
          u32x16 a = load_u32x16(data + i + 0 * (1 << (k - 2)) + j);
          u32x16 b = load_u32x16(data + i + 1 * (1 << (k - 2)) + j);
          u32x16 c = load_u32x16(data + i + 2 * (1 << (k - 2)) + j);
          u32x16 d = load_u32x16(data + i + 3 * (1 << (k - 2)) + j);
          a = mts.shrink2(a), b = mts.mul(b, w1), c = mts.mul(c, w2), d = mts.mul(d, w3);
          u32x16 a1 = mts.shrink2(a + c), b1 = mts.shrink2(b + d), c1 = mts.shrink2_n(a - c), d1 = mts.mul(b + mts.mod2 - d, w_1);
          store_u32x16(data + i + 0 * (1 << (k - 2)) + j, a1 + b1);
          store_u32x16(data + i + 1 * (1 << (k - 2)) + j, a1 + mts.mod2 - b1);
          store_u32x16(data + i + 2 * (1 << (k - 2)) + j, c1 + d1);
          store_u32x16(data + i + 3 * (1 << (k - 2)) + j, c1 + mts.mod2 - d1);
        }
      }
    }
    assert(k == 4);
    u32x16 cum = (u32x16)_mm512_setr_epi32(w[0], w[0], w[1], w[0],   // [ w         | w^2       | w * w_1    | w^4       ]
                                           w[2], w[1], w[3], w[0],   // [ w * w_2   | w^2 * w_1 | w * w_3    | w^8       ]
                                           w[4], w[2], w[5], w[1],   // [ w * w_4   | w^2 * w_2 | w * w_5    | w^4 * w_1 ]
                                           w[6], w[3], w[7], w[0]);  // [ w * w_6   | w^2 * w_3 | w * w_7    | w^8       ]
    u32 n_16 = n / 16;
    for (u32 i = 0; i < n_16; ++i) {
      u32x16 val = load_u32x16(data + i * 16);
      u64x8 w3 = (u64x8)cum;  // no shuffle needed
      u64x8 w2 = (u64x8)shuffle_u32x16<0b00'01'00'01>(cum);
      u64x8 w1 = (u64x8)permute_u32x16(cum, (u32x16)setr_u64x8(3, 3, 3, 3, 11, 11, 11, 11));
      u64x8 w0 = (u64x8)permute_u32x16(cum, (u32x16)setr_u64x8(7, 7, 7, 7, 15, 15, 15, 15));
      cum = mts.mul<true>(cum, w_cum_x16[__builtin_ctz(~i)]);
      u32x16 bw;
      val = mts.shrink2(val);
      bw = permute_u32x16((u32x16)mts.mul_to_hi(w0, (u64x8)permute_u32x16(val, (u32x16)setr_u64x8(8, 9, 10, 11, 12, 13, 14, 15))), (u32x16)setr_u32x16_si256(1, 3, 5, 7, 9, 11, 13, 15));
      val = permute_u32x16_epi128<0b01'00'01'00>(val) + blend_u32x16<0xFF00>(bw, mts.mod2 - bw);
      val = mts.shrink2(val);
      bw = permute_u32x16((u32x16)mts.mul_to_hi(w1, (u64x8)permute_u32x16(val, (u32x16)setr_u64x8(4, 5, 6, 7, 12, 13, 14, 15))), (u32x16)_mm512_setr_epi32(1, 3, 5, 7, 1, 3, 5, 7, 9, 11, 13, 15, 9, 11, 13, 15));
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
  [[gnu::noinline]] __attribute__((optimize("O3"))) void ifft(u32 lg, u32 *data, u32 fc = -1u) const {
    const auto mt = this->mt;    // ! to put Montgomery constants in registers
    const auto mts = this->mts;  // ! to put Montgomery constants in registers
    if (fc == -1u) fc = mt.r;
    u32 n = 1 << lg, k = 1;
    u32x16 cum2 = (u32x16)_mm512_setr_epi32(w_r[0], w_r[0], w_r[0], w_r[1], w_r[0], w_r[2], w_r[0], w_r[3],
                                            w_r[0], w_r[4], w_r[0], w_r[5], w_r[0], w_r[6], w_r[0], w_r[7]);
    u32x16 cum1 = (u32x16)_mm512_setr_epi32(w_r[0], w_r[0], w_r[0], w_r[0], w_r[0], w_r[0], w_r[1], w_r[1],
                                            w_r[0], w_r[0], w_r[2], w_r[2], w_r[0], w_r[0], w_r[3], w_r[3]);
    u32x16 cum0 = (u32x16)_mm512_setr_epi32(w_r[0], w_r[0], w_r[0], w_r[0], w_r[0], w_r[0], w_r[0], w_r[0],
                                            w_r[0], w_r[0], w_r[0], w_r[0], w_r[1], w_r[1], w_r[1], w_r[1]);
    const u32 inv_2 = mt.mul<true>(mt.r2, (mod + 1) / 2);
    u32x16 cum = set1_u32x16(mt.mul<true>(fc, power(inv_2, lg)));
    u32 n_16 = n / 16;
    for (u32 i = 0; i < n_16; ++i) {
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
      for (u32 i = 0; i < n; i += (1 << (k + 1))) {
        u32x16 w1 = shuffle_u32x16<0b00'00'00'00>((u32x16)wj_cum);
        u32x16 w2 = permute_u32x16((u32x16)wj_cum, set1_u32x16(2));
        u32x16 w3 = permute_u32x16((u32x16)wj_cum, set1_u32x16(6));
        wj_cum = mts.mul<true>(wj_cum, w_rcum_x8[__builtin_ctz(~(i >> (k + 1)))]);
        for (u32 j = 0; j < (1 << (k - 1)); j += 16) {
          u32x16 a = load_u32x16(data + i + 0 * (1 << (k - 1)) + j), b = load_u32x16(data + i + 1 * (1 << (k - 1)) + j);
          u32x16 c = load_u32x16(data + i + 2 * (1 << (k - 1)) + j), d = load_u32x16(data + i + 3 * (1 << (k - 1)) + j);
          u32x16 a1 = mts.shrink2(a + b), b1 = mts.shrink2_n(a - b), c1 = mts.shrink2(c + d), d1 = mts.mul(c + mts.mod2 - d, w_1);
          store_u32x16(data + i + 0 * (1 << (k - 1)) + j, mts.shrink2(a1 + c1));
          store_u32x16(data + i + 1 * (1 << (k - 1)) + j, mts.mul(w1, b1 + d1));
          store_u32x16(data + i + 2 * (1 << (k - 1)) + j, mts.mul(w2, a1 + mts.mod2 - c1));
          store_u32x16(data + i + 3 * (1 << (k - 1)) + j, mts.mul(w3, b1 + mts.mod2 - d1));
        }
      }
    }
    if (k == lg) {
      for (u32 i = 0; i < n / 2; i += 16) {
        u32x16 a = load_u32x16(data + i), b = load_u32x16(data + n / 2 + i);
        store_u32x16(data + i, mts.shrink(mts.shrink2(a + b)));
        store_u32x16(data + n / 2 + i, mts.shrink(mts.shrink2_n(a - b)));
      }
    } else {
      assert(k == lg + 1);
      for (u32 i = 0; i < n; i += 16) {
        u32x16 ai = load_u32x16(data + i);
        store_u32x16(data + i, mts.shrink(ai));
      }
    }
  }

  __attribute__((optimize("O3"))) vec<u32> conv_slow(vec<u32> a, vec<u32> b) const {
    u32 sz = std::max<u32>(0, u32(a.size() + b.size() - 1));
    const auto mt = this->mt;  // ! to put Montgomery constants in registers
    vec<u32> c(sz);
    for (u32 i = 0; i < a.size(); ++i)
      for (u32 j = 0; j < b.size(); ++j) {
        // c[i + j] = (c[i + j] + u64(a[i]) * b[j]) % mod;
        c[i + j] = mt.shrink(c[i + j] + mt.mul<true>(mt.r2, mt.mul(a[i], b[j])));
      }
    return c;
  }

  // a and b should be 64-byte aligned
  // writes (a * b) to a
  [[gnu::noinline]] __attribute__((optimize("O3"))) void conv(u32 lg, __restrict__ pu32 a, __restrict__ pu32 b) const {
    if (lg <= 4) {
      u32 n = (1 << lg);
      __restrict__ pu32 c = (pu32)_mm_malloc(n * 4, 4);
      memset(c, 0, 4 * n);
      for (u32 i = 0; i < n; ++i)
        for (u32 j = 0; j < n; ++j) c[(i + j) & (n - 1)] = mt.shrink2(c[(i + j) & (n - 1)] + mt.mul(a[i], b[j]));
      for (u32 i = 0; i < n; ++i) a[i] = mt.mul<true>(mt.r2, c[i]);
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

  __attribute__((optimize("O3"))) vec<u32> conv(const vec<u32> &a, const vec<u32> &b) const {
    u32 sz = std::max<u32>(0, u32(a.size() + b.size() - 1));
    u32 lg = u32(std::__lg(std::max<u32>(1, sz - 1)) + 1);
    pu32 ap = (pu32)_mm_malloc((usz)std::max(64, (1 << lg) * 4), 64);
    pu32 bp = (pu32)_mm_malloc((usz)std::max(64, (1 << lg) * 4), 64);
    memset(ap, 0, usz(4 << lg));
    memset(bp, 0, usz(4 << lg));
    std::copy(a.begin(), a.end(), ap);
    std::copy(b.begin(), b.end(), bp);
    conv(lg, ap, bp);
    vec<u32> res(ap, ap + sz);
    _mm_free(ap);
    _mm_free(bp);
    return res;
  }
};

}  // namespace tifa_libs::math

#endif