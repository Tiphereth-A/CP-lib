#ifndef TIFALIBS_MATH_BARRETT
#define TIFALIBS_MATH_BARRETT

#include "../util/alias_num.hpp"

namespace tifa_libs::math {

template <u32 MOD, u64 B_ = 1>
struct barrett {
  static CEXP u64 B = B_ % MOD, R = ((u128)B << 64) / MOD;

  static CEXP u32 reduce(u64 a) NE {
    if (u64 q = u64((u128)a * R >> 64); (a = (u64)a * B - q * MOD) >= MOD) a -= MOD;
    return (u32)a;
  }
};
template <>  // dynamic
struct barrett<0> {
  u32 mod;
  u64 b, r;

  CEXPE barrett(u32 mod, u64 b = 1) NE { reset(mod, b); }
  CEXP void reset(u32 mod_, u64 b_ = 1) NE { assert(mod_), mod = mod_, b = b_ % mod, r = (u64(((u128)b << 64) / mod)); }
  CEXP u32 reduce(u64 a) CNE {
    if (u64 q = u64((u128)a * r >> 64); (a = (u64)a * b - q * mod) >= mod) a -= mod;
    return (u32)a;
  }
};

}  // namespace tifa_libs::math

#endif