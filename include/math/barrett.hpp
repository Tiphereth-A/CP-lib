#ifndef TIFALIBS_MATH_BARRETT
#define TIFALIBS_MATH_BARRETT

#include "../util/alias_num.hpp"

namespace tifa_libs::math {

template <u64 MOD, u64 B_ = 1>
struct barrett {
  static CEXP u64 B = B_ % MOD, R = ((u128)B << 64) / MOD;

  static CEXP u64 reduce(u64 a) NE {
    if (u64 q = u64((u128)a * R >> 64); (a = a * B - q * MOD) >= MOD) a -= MOD;
    return a;
  }
};
template <>  // dynamic
struct barrett<0> {
  u64 mod, b, r;

  CEXPE barrett(u64 mod, u64 b = 1) NE { reset(mod, b); }
  CEXP void reset(u64 mod_, u64 b_ = 1) NE { assert(mod_), mod = mod_, b = b_ % mod, r = (u64(((u128)b << 64) / mod)); }
  CEXP u64 reduce(u64 a) CNE {
    if (u64 q = u64((u128)a * r >> 64); (a = a * b - q * mod) >= mod) a -= mod;
    return a;
  }
};

}  // namespace tifa_libs::math

#endif