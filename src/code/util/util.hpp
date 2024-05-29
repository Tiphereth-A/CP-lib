#ifndef TIFALIBS_UTIL_UTIL
#define TIFALIBS_UTIL_UTIL

#include <bits/stdc++.h>

#define CEXP constexpr
#define TPN typename
#define CR const&

#define cT_(...) std::conditional_t<sizeof(__VA_ARGS__) <= sizeof(size_t), __VA_ARGS__, __VA_ARGS__ CR>
#define fle_(T, i, l, r, ...) for (T i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i <= i##e; ++i)
#define flt_(T, i, l, r, ...) for (T i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i < i##e; ++i)

#ifdef ONLINE_JUDGE
#undef assert
#define assert(x) 42
#endif

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

template <class T, usz N>
using arr = std::array<T, N>;
template <class T>
using vec = std::vector<T>;
template <class T>
using vvec = vec<vec<T>>;
template <class T>
using v3ec = vec<vvec<T>>;
template <class U, class T>
using vecp = vec<std::pair<U, T>>;
template <class U, class T>
using vvecp = vvec<std::pair<U, T>>;
template <class T>
using vecpt = vec<ptt<T>>;
template <class T>
using vvecpt = vvec<ptt<T>>;

template <class T, class C = std::less<T>>
using pq = std::priority_queue<T, vec<T>, C>;
template <class T>
using pqg = std::priority_queue<T, vec<T>, std::greater<T>>;

using strn = std::string;
using strnv = std::string_view;

using vecu = vec<u32>;
using vvecu = vvec<u32>;
using v3ecu = v3ec<u32>;
using vecu64 = vec<u64>;
using vecb = vec<bool>;
using vvecb = vvec<bool>;

using namespace std::literals;

CEXP i8 operator""_i8(unsigned long long x) { return (i8)x; }
CEXP i16 operator""_i16(unsigned long long x) { return (i16)x; }
CEXP i32 operator""_i32(unsigned long long x) { return (i32)x; }
CEXP i64 operator""_i64(unsigned long long x) { return (i64)x; }
CEXP isz operator""_iz(unsigned long long x) { return (isz)x; }

CEXP u8 operator""_u8(unsigned long long x) { return (u8)x; }
CEXP u16 operator""_u16(unsigned long long x) { return (u16)x; }
CEXP u32 operator""_u32(unsigned long long x) { return (u32)x; }
CEXP u64 operator""_u64(unsigned long long x) { return (u64)x; }
CEXP usz operator""_uz(unsigned long long x) { return (usz)x; }

inline const auto fn_0 = [](auto&&...) {};
inline const auto fn_is0 = [](auto x) { return x == 0; };

template <std::floating_point FP>
inline FP eps_v = std::sqrt(std::numeric_limits<FP>::epsilon());
template <std::floating_point FP>
CEXP void set_eps(FP v) { eps_v<FP> = v; }
using std::numbers::pi_v;

namespace tifa_libs {
using std::min, std::max, std::swap;
template <class T>
constexpr T abs(T x) { return x < 0 ? -x : x; }
}  // namespace tifa_libs

#endif