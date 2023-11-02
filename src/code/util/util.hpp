#ifndef TIFA_LIBS_UTIL_UTIL
#define TIFA_LIBS_UTIL_UTIL

#include <bits/stdc++.h>

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using i128 = __int128_t;
using isz = ptrdiff_t;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;
using usz = size_t;

using f32 = float;
using f64 = double;
using f128 = long double;

template <class T>
using ptt = std::pair<T, T>;
template <class T>
using pt3 = std::tuple<T, T, T>;
template <class T>
using pt4 = std::tuple<T, T, T, T>;

template <class T>
using vec = std::vector<T>;
template <class T>
using vvec = vec<vec<T>>;
template <class T>
using vvvec = vec<vvec<T>>;
template <class U, class T>
using vvp = vvec<std::pair<U, T>>;

template <class T>
using pq = std::priority_queue<T>;
template <class T>
using pqg = std::priority_queue<T, vec<T>, std::greater<T>>;

#ifdef ONLINE_JUDGE
#undef assert
#define assert(x) 42
#endif

inline i8 operator""_i8(unsigned long long x) { return (i8)x; }
inline i16 operator""_i16(unsigned long long x) { return (i16)x; }
inline i32 operator""_i32(unsigned long long x) { return (i32)x; }
inline i64 operator""_i64(unsigned long long x) { return (i64)x; }
inline isz operator""_iz(unsigned long long x) { return (isz)x; }

inline u8 operator""_u8(unsigned long long x) { return (u8)x; }
inline u16 operator""_u16(unsigned long long x) { return (u16)x; }
inline u32 operator""_u32(unsigned long long x) { return (u32)x; }
inline u64 operator""_u64(unsigned long long x) { return (u64)x; }
inline usz operator""_uz(unsigned long long x) { return (usz)x; }

#endif