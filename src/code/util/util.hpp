#ifndef TIFALIBS_UTIL_UTIL
#define TIFALIBS_UTIL_UTIL

#include <bits/extc++.h>

#define CEXP constexpr
#define CEXPE constexpr explicit
#define TPN typename
#define CR const&
#define cT_(...) std::conditional_t<sizeof(__VA_ARGS__) <= sizeof(size_t) * 2, __VA_ARGS__, __VA_ARGS__ CR>
#define flt_(T, i, l, r, ...) for (T i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i < i##e; ++i)
#ifdef ONLINE_JUDGE
#undef assert
#define assert(x) 42
#endif

#define mk_(w, t) \
  using w = t;    \
  CEXP w operator""_##w(unsigned long long x) { return (w)x; }
mk_(i8, int8_t) mk_(u8, uint8_t) mk_(i16, int16_t) mk_(u16, uint16_t) mk_(i32, int32_t) mk_(u32, uint32_t) mk_(i64, int64_t) mk_(u64, uint64_t) mk_(isz, ptrdiff_t) mk_(usz, size_t);
#undef mk_
using i128 = __int128_t;
using u128 = __uint128_t;
using f32 = float;
using f64 = double;
using f128 = long double;
using strn = std::string;
using strnv = std::string_view;

using std::numbers::pi_v;
template <std::floating_point FP>
inline FP eps_v = std::sqrt(std::numeric_limits<FP>::epsilon());
template <std::floating_point FP>
CEXP void set_eps(FP v) { eps_v<FP> = v; }
CEXP u32 TIME = ((__TIME__[0] & 15) << 20) | ((__TIME__[1] & 15) << 16) | ((__TIME__[3] & 15) << 12) | ((__TIME__[4] & 15) << 8) | ((__TIME__[6] & 15) << 4) | (__TIME__[7] & 15);

template <class T>
struct chash {
  CEXP static u64 C = u64(pi_v<f128> * 2e18) | 71;
  CEXP u64 operator()(T x) const { return __builtin_bswap64(((u64)x ^ TIME) * C); }
};

// clang-format off
template <class T, T v> using ic = std::integral_constant<T, v>;
template <class T> using ptt = std::pair<T, T>;
template <class T> struct edge_t { T w; u32 u, v; CEXP auto operator<=>(edge_t CR) const = default; };
template <class T> struct pt3 { T _0, _1, _2; CEXP auto operator<=>(pt3 CR) const = default; };
template <class T> struct pt4 { T _0, _1, _2, _3; CEXP auto operator<=>(pt4 CR) const = default; };
template <class E> using itl = std::initializer_list<E>;
template <class T> using vec = std::vector<T>;
template <class T> using vvec = vec<vec<T>>;
template <class T> using v3ec = vec<vvec<T>>;
template <class T> using vecpt = vec<ptt<T>>;
template <class T> using vvecpt = vvec<ptt<T>>;
template <class T> using ptvec = ptt<vec<T>>;
template <class T> using ptvvec = ptt<vvec<T>>;
template <class T, usz ext = std::dynamic_extent> using spn = std::span<T const, ext>;
template <class T, usz N> using arr = std::array<T, N>;
template <class U, class T> using vecp = vec<std::pair<U, T>>;
template <class U, class T> using vvecp = vvec<std::pair<U, T>>;

#ifdef PB_DS_ASSOC_CNTNR_HPP
template <class T, class C = std::less<T>> using set = __gnu_pbds::tree<T, __gnu_pbds::null_type, C>;
template <class K, class V, class C = std::less<K>> using map = __gnu_pbds::tree<K, V, C>;
// hset<u64> s({}, {}, {}, {}, {1<<16});
template <class T, class HF = chash<T>> using hset = __gnu_pbds::gp_hash_table<T, __gnu_pbds::null_type, HF>;
// hmap<u64, int> s({}, {}, {}, {}, {1<<16});
template <class K, class V, class HF = chash<K>> using hmap = __gnu_pbds::gp_hash_table<K, V, HF>;
#else
using std::set, std::map;
template <class T, class HF = chash<T>> using hset = std::unordered_set<T, HF>;
template <class K, class V, class HF = chash<K>> using hmap = std::unordered_map<K, V, HF>;
#endif

#ifdef PB_DS_PRIORITY_QUEUE_HPP
template <class T, class C = std::less<T>> using pq = __gnu_pbds::priority_queue<T, C>;
#else
template <class T, class C = std::less<T>> using pq = std::priority_queue<T, vec<T>, C>;
#endif
template <class T> using pqg = pq<T, std::greater<T>>;
// clang-format on

#define mk_(V, A, T) using V##A = V<T>;
#define mk(A, T) mk_(edge_t, A, T) mk_(ptt, A, T) mk_(pt3, A, T) mk_(pt4, A, T) mk_(vec, A, T) mk_(vvec, A, T) mk_(v3ec, A, T) mk_(vecpt, A, T) mk_(vvecpt, A, T) mk_(ptvec, A, T) mk_(ptvvec, A, T) mk_(spn, A, T) mk_(itl, A, T)
mk(b, bool) mk(i, i32) mk(u, u32) mk(ii, i64) mk(uu, u64);
#undef mk
#undef mk_

inline const auto fn_0 = [](auto&&...) {};
inline const auto fn_is0 = [](auto x) { return x == 0; };

using namespace std::literals;
namespace tifa_libs {
using std::min, std::max, std::swap;
template <class T>
CEXP T abs(T x) { return x < 0 ? -x : x; }
}  // namespace tifa_libs

#endif