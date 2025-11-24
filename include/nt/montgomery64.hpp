#ifndef TIFALIBS_NT_MONTGOMERY64
#define TIFALIBS_NT_MONTGOMERY64

#include "../util/alias_num.hpp"

namespace tifa_libs::math {

template <u64 MOD>
struct montgomery64 {
  static CEXP u64 R = [] {
    u64 t = 2, iv = MOD * (t - MOD * MOD);
    iv *= t - MOD * iv, iv *= t - MOD * iv, iv *= t - MOD * iv;
    return iv * (t - MOD * iv);
  }();
  static CEXP u64 R2 = [] {
    u64 iv = -MOD % MOD;
    for (u32 i = 0; i != 64; ++i)
      if ((iv *= 2) >= MOD) iv -= MOD;
    return iv;
  }();
  static_assert(MOD & 1);
  static_assert(R * MOD == 1);
  static_assert((MOD >> 63) == 0);
  static_assert(MOD != 1);
  static CEXP u64 mulh(u64 x, u64 y) NE {
    u64 a = x >> 32, b = (u32)(x), c = y >> 32, d = (u32)(y), ad = a * d, bc = b * c;
    return a * c + (ad >> 32) + (bc >> 32) + (((ad & 0xFFFFFFFF) + (bc & 0xFFFFFFFF) + (b * d >> 32)) >> 32);
  }
  static CEXP u64 redc_mul(u64 x, u64 y) NE {
    u64 res = mulh(x, y) - mulh(x * y * R, MOD);
    return res + (MOD & -(res >> 63));
  }
  static CEXP u64 norm(i64 x) NE { return (u64)x + (MOD & u64(-(x < 0))); }
};
template <>  // dynamic
struct montgomery64<0> {
  u64 MOD, R, R2;
  CEXP montgomery64() NE = default;
  CEXPE montgomery64(u64 m) NE { reset(m); }
  CEXP void reset(u64 m) NE {
    assert(!((m & 1) == 0 || m == 1 || m >> 63)), MOD = m;
    u64 t = 2, iv = MOD * (t - MOD * MOD);
    iv *= t - MOD * iv, iv *= t - MOD * iv, iv *= t - MOD * iv, R = iv * (t - MOD * iv), R2 = -MOD % MOD;
    flt_ (u32, i, 0, 64)
      if ((R2 *= 2) >= MOD) R2 -= MOD;
  }
  CEXP u64 mul_h(u64 x, u64 y) CNE {
    u64 a = x >> 32, b = (u32)x, c = y >> 32, d = (u32)y, ad = a * d, bc = b * c;
    return a * c + (ad >> 32) + (bc >> 32) + (((ad & 0xFFFFFFFF) + (bc & 0xFFFFFFFF) + (b * d >> 32)) >> 32);
  }
  CEXP u64 redc_mul(u64 x, u64 y) CNE {
    u64 res = mul_h(x, y) - mul_h(x * y * R, MOD);
    return res + (MOD & -(res >> 63));
  }
  CEXP u64 norm(i64 x) CNE { return u64(x + i64(MOD & u64(-(x < 0)))); }
};

}  // namespace tifa_libs::math

#endif