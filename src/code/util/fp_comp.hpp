#ifndef TIFALIBS_UTIL_FP_COMP
#define TIFALIBS_UTIL_FP_COMP

#include "fp_const.hpp"
#include "traits.hpp"

namespace tifa_libs {

template <int_c FP>
constexpr int sgn(FP x) { return (!!x) | (x >> (sizeof(FP) * 8 - 1)); }
template <std::floating_point FP>
constexpr int sgn(FP x) { return (x > eps_v<FP>)-(x < -eps_v<FP>); }

template <class FP>
constexpr bool is_neg(FP x) { return sgn(x) < 0; }
template <class FP>
constexpr bool is_zero(FP x) { return !sgn(x); }
template <class FP>
constexpr bool is_pos(FP x) { return sgn(x) > 0; }

template <int_c FP>
constexpr int comp(FP l, FP r) { return sgn(l - r); }
template <int_c FP>
constexpr bool is_lt(FP l, FP r) { return comp(l, r) < 0; }
template <int_c FP>
constexpr bool is_eq(FP l, FP r) { return !comp(l, r); }
template <int_c FP>
constexpr bool is_gt(FP l, FP r) { return comp(l, r) > 0; }

template <std::floating_point FP>
constexpr int comp(FP l, FP r) { return sgn((l - r) / std::max({std::abs(l), std::abs(r), FP(1)})); }
template <std::floating_point FP>
constexpr bool is_lt(FP l, FP r) { return comp(l, r) < 0; }
template <std::floating_point FP>
constexpr bool is_eq(FP l, FP r) { return !comp(l, r); }
template <std::floating_point FP>
constexpr bool is_gt(FP l, FP r) { return comp(l, r) > 0; }

}  // namespace tifa_libs

#endif