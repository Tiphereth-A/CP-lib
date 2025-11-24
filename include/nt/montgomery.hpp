#ifndef TIFALIBS_NT_MONTGOMERY
#define TIFALIBS_NT_MONTGOMERY

#include "../util/alias_num.hpp"

namespace tifa_libs::math {

template <u32 MOD>
struct montgomery {
  static CEXP u32 MOD2 = MOD << 1, R2 = -(u64)(MOD) % MOD, R = [] {
    u32 t = 2, iv = MOD * (t - MOD * MOD);
    iv *= t - MOD * iv, iv *= t - MOD * iv;
    return iv * (MOD * iv - t);
  }();
  static_assert(MOD & 1);
  static_assert(-R * MOD == 1);
  static_assert((MOD >> 30) == 0);
  static_assert(MOD != 1);
  static CEXP u32 reduce(u64 x) NE { return u32((x + u64((u32)x * R) * MOD) >> 32); }
  static CEXP u32 norm(u32 x) NE { return x - (MOD & -((MOD - 1 - x) >> 31)); }
};
template <>  // dynamic
struct montgomery<0> {
  u32 R, R2, MOD, MOD_ODD, OFFSET, MASK;
  CEXP montgomery() NE = default;
  CEXPE montgomery(u32 m) NE { reset(m); }
  CEXP void reset(u32 m) NE {
    for (assert(!(m == 1 || m >> 31)), MOD = MOD_ODD = m, OFFSET = 0; (MOD_ODD & 1) == 0; ++OFFSET, MOD_ODD /= 2);
    MASK = (1_u32 << OFFSET) - 1_u32;
    u32 t = 2, iv = MOD_ODD * (t - MOD_ODD * MOD_ODD);
    iv *= t - MOD_ODD * iv, iv *= t - MOD_ODD * iv, R = iv * (MOD_ODD * iv - t), R2 = u32(-u64(MOD_ODD) % MOD_ODD);
  }
  CEXP u32 norm(i32 x) CNE { return u32(x + (-(x < 0) & (i32)MOD)); }
  CEXP u32 reduce(u64 x) CNE {
    u32 t = u32((x + u64((u32)x * R) * MOD_ODD) >> 32);
    return t - (MOD_ODD & -((MOD_ODD - 1 - t) >> 31));
  }
  CEXP u32 tsf(u32 x) CNE { return reduce(u64(x % MOD_ODD) * R2) << OFFSET | (x & MASK); }
};

}  // namespace tifa_libs::math

#endif