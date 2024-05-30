#ifndef TIFALIBS_MATH_RATIONAL_APPROX
#define TIFALIBS_MATH_RATIONAL_APPROX

#include "../opt/bsearch.hpp"
#include "../util/traits.hpp"

namespace tifa_libs::math {

// @return {xl/yl, xr/yr} such that:
// 1. xl/yl < f < xr/yr
// 2. xl/yl be maximal
// 3. xr/yr be minimal
// 4. 0 <= xl,xr,yl,yr <= n
template <uint_c T>
CEXP ptt<ptt<T>> rational_approx(T n, ptt<T> CR f) {
  auto ff = [](ptt<T> CR a, u32 b, ptt<T> CR c) { return ptt<T>{a.first * b + c.first, a.second * b + c.second}; };
  ptt<T> lo{0, 1}, hi{1, 0};
  while (true) {
    const u32 n1 = opt::bsearch([&](u32 x) {
      const auto _ = ff(hi, x, lo);
      return _.first <= n && _.second <= n && _.first * f.second <= _.second * f.first;
    });
    lo = ff(hi, n1, lo);
    if (lo.first * f.second == lo.second * f.first) {
      hi = lo;
      break;
    }
    const u32 n2 = opt::bsearch([&](u32 x) {
      const auto _ = ff(lo, x, hi);
      return _.first <= n && _.second <= n && f.first * _.second <= f.second * _.first;
    });
    hi = ff(lo, n2, hi);
    if (hi.first * f.second == hi.second * f.first) {
      lo = hi;
      break;
    }
    if (!n1 && !n2) break;
  }
  return {lo, hi};
}

}  // namespace tifa_libs::math

#endif