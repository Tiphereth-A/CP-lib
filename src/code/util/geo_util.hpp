#ifndef TIFA_LIBS_UTIL_GEO_UTIL
#define TIFA_LIBS_UTIL_GEO_UTIL

#include "util.hpp"

namespace tifa_libs::geo {

// const FP EPS = std::sqrt(std::numeric_limits<FP>::epsilon());
template <class FP>
constexpr FP EPS = 1e-8;
template <class FP>
const FP PI = std::acos((FP)-1);

// #define RELATIVE_ERR__

template <class FP, std::enable_if_t<std::is_integral_v<FP>>* = nullptr>
constexpr int sgn(FP x) { return x < 0 ? -1 : x > 0; }
template <class FP, std::enable_if_t<std::is_floating_point_v<FP>>* = nullptr>
constexpr int sgn(FP x) { return x < -EPS<FP> ? -1 : x > EPS<FP>; }
template <class FP>
constexpr bool is_neg(FP x) { return sgn(x) < 0; }
template <class FP>
constexpr bool is_zero(FP x) { return sgn(x) == 0; }
template <class FP>
constexpr bool is_pos(FP x) { return sgn(x) > 0; }

template <class FP>
constexpr int comp(FP l, FP r) { return sgn(l - r); }
template <class FP>
constexpr bool is_le(FP l, FP r) { return is_neg(l - r); }
template <class FP>
constexpr bool is_eq(FP l, FP r) { return is_zero(l - r); }
template <class FP>
constexpr bool is_ge(FP l, FP r) { return is_pos(l - r); }

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

}  // namespace tifa_libs::geo

#endif