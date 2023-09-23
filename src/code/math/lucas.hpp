#ifndef TIFA_LIBS_MATH_LUCAS
#define TIFA_LIBS_MATH_LUCAS

#include "../util/util.hpp"

#include "mcn_mod.hpp"

namespace tifa_libs::math {

class Lucas {
  MCN mCn;

  u64 lucas__(const MCN &mCn, u64 m, u64 n) const {
    const u64 mod = mCn.mod();
    return n == 0 ? 1 : mCn((i64)(m % mod), (i64)(n % mod)) * lucas__(mCn, m / mod, n / mod) % mod;
  }

public:
  // @param p MUSU be prime
  explicit Lucas(u32 p):
    mCn(p, p) { assert(p > 1 && p < 10'000'000); }

  u64 operator()(i64 m, i64 n) const { return m < n || n < 0 ? 0 : lucas__(mCn, (u64)m, (u64)n); }
};

}  // namespace tifa_libs::math

#endif