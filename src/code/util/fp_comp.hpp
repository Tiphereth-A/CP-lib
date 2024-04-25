#ifndef TIFALIBS_UTIL_FP_COMP
#define TIFALIBS_UTIL_FP_COMP

#include "traits.hpp"

namespace tifa_libs {

template <sint_c T>
CEXP int sgn(T x) { return (!!x) | (x >> (sizeof(T) * 8 - 1)); }
template <uint_c T>
CEXP int sgn(T x) { return !!x; }
template <std::floating_point FP>
CEXP int sgn(FP x) { return (x > eps_v<FP>)-(x < -eps_v<FP>); }

template <class FP>
CEXP bool is_neg(FP x) { return sgn(x) < 0; }
template <class FP>
CEXP bool is_zero(FP x) { return !sgn(x); }
template <class FP>
CEXP bool is_pos(FP x) { return sgn(x) > 0; }

template <int_c T>
CEXP int comp(T l, T r) { return sgn(l - r); }
template <std::floating_point FP>
CEXP int comp(FP l, FP r) { return sgn((l - r) / max({abs(l), abs(r), FP(1)})); }

template <class FP>
CEXP bool is_lt(FP l, FP r) { return comp(l, r) < 0; }
template <class FP>
CEXP bool is_eq(FP l, FP r) { return !comp(l, r); }
template <class FP>
CEXP bool is_gt(FP l, FP r) { return comp(l, r) > 0; }

}  // namespace tifa_libs

#endif