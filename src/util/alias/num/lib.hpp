#pragma once

#include "../../util/lib.hpp"
// clang-format off
namespace tifa_libs {

#define mk0_(w, t) using w = t; using c##w = const t
#define mk_(w, t) mk0_(w, t); CEXP w operator""_##w(unsigned long long x) NE { return (w)x; }
mk_(i8, int8_t) mk_(u8, uint8_t) mk_(i16, int16_t) mk_(u16, uint16_t) mk_(i32, int32_t) mk_(u32, uint32_t) mk_(i64, int64_t) mk_(u64, uint64_t) mk_(isz, ssize_t) mk_(usz, size_t) mk_(chr, char) mk_(schr, signed char) mk_(uchr, unsigned char) mk_(sint, signed) mk_(uint, unsigned);
mk0_(i128, __int128_t); mk0_(u128, __uint128_t); mk0_(f32, float); mk0_(f64, double); mk0_(f128, long double);
#undef mk0_
#undef mk_

}  // namespace tifa_libs
// clang-format on
