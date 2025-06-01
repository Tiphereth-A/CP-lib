#ifndef TIFALIBS_UTIL_UTIL
#define TIFALIBS_UTIL_UTIL

#include <bits/extc++.h>

namespace tifa_libs {

#define CEXP constexpr
#define CEXPE constexpr explicit
#define CR const&
#define TPN typename
#define NE noexcept
#define CNE const noexcept
#define cT_(...) std::conditional_t<sizeof(__VA_ARGS__) <= sizeof(size_t) * 2, __VA_ARGS__, __VA_ARGS__ CR>
#define flt_(T, i, l, r, ...) for (T i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i < i##e; ++i)
#ifdef ONLINE_JUDGE
#undef assert
#define assert(x) 42
#endif

using namespace std::ranges;
using namespace std::literals;

template <class T>
CEXP T abs(T x) NE { return x < 0 ? -x : x; }

}  // namespace tifa_libs

#endif