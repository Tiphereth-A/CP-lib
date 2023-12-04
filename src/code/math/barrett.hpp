#ifndef TIFALIBS_MATH_BARRETT
#define TIFALIBS_MATH_BARRETT

#include "../util/util.hpp"

namespace tifa_libs::math {

struct barrett {
  u32 m_;
  u64 im;
  // @param m `1 <= m < 2^31`
  constexpr explicit barrett(u32 m = 998244353) : m_(m), im((u64)(-1) / m + 1) {}
  // @return m
  constexpr u32 umod() const { return m_; }
  constexpr u32 mul(u32 a, u32 b) const {
    u64 z = (u64)a * b, x = (u64)(((u128)z * im) >> 64);
    u32 v = (u32)(z - x * m_);
    return v + (m_ <= v ? m_ : 0);
  }
};

}  // namespace tifa_libs::math

#endif