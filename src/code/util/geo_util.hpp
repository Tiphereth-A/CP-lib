#ifndef TIFA_LIBS_UTIL_GEO_UTIL
#define TIFA_LIBS_UTIL_GEO_UTIL

#include "util.hpp"

namespace tifa_libs::geo2d {

constexpr double EPS = 1e-8;
const double PI = std::acos(-1.);

// #define RELATIVE_ERR__

#ifdef RELATIVE_ERR__
#define DIFF__(x, y) (((x) - (y)) / std::abs(x))
#undef RELATIVE_ERR__
#else
#define DIFF__(x, y) ((x) - (y))
#endif

template <class FP>
constexpr int sgn(FP x) { return x < -EPS ? -1 : x > EPS; }
template <class FP>
constexpr bool is_neg(FP x) { return sgn(x) < 0; }
template <class FP>
constexpr bool is_zero(FP x) { return sgn(x) == 0; }
template <class FP>
constexpr bool is_pos(FP x) { return sgn(x) > 0; }

template <class FP>
constexpr int comp(FP l, FP r) { return sgn(DIFF__(l, r)); }
template <class FP>
constexpr bool is_le(FP l, FP r) { return is_neg(DIFF__(l, r)); }
template <class FP>
constexpr bool is_eq(FP l, FP r) { return is_zero(DIFF__(l, r)); }
template <class FP>
constexpr bool is_ge(FP l, FP r) { return is_pos(DIFF__(l, r)); }
#undef DIFF__

//! containing endpoints
template <class FP>
constexpr bool is_intersect(FP l1, FP r1, FP l2, FP r2) {
  if (l1 > r1) std::swap(l1, r1);
  if (l2 > r2) std::swap(l2, r2);
  return !(is_le(r1, l2) || is_le(r2, l1));
}
//! containing endpoints
template <class FP>
constexpr bool is_in_middle(FP l, FP mid, FP r) { return is_eq(l, mid) || is_eq(r, mid) || ((l < mid) ^ (r < mid)); }

}  // namespace tifa_libs::geo2d

#endif