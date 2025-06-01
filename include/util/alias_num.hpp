#ifndef TIFALIBS_UTIL_ALIAS_NUM
#define TIFALIBS_UTIL_ALIAS_NUM

#include "util.hpp"

namespace tifa_libs {

#define mk_(w, t) \
  using w = t;    \
  CEXP w operator""_##w(unsigned long long x) NE { return (w)x; }
mk_(i8, int8_t) mk_(u8, uint8_t) mk_(i16, int16_t) mk_(u16, uint16_t) mk_(i32, int32_t) mk_(u32, uint32_t) mk_(i64, int64_t) mk_(u64, uint64_t) mk_(isz, ptrdiff_t) mk_(usz, size_t);
#undef mk_
using i128 = __int128_t;
using u128 = __uint128_t;
using f32 = float;
using f64 = double;
using f128 = long double;

}  // namespace tifa_libs

#endif