#ifndef TIFALIBS_UTIL_FP_FUNC
#define TIFALIBS_UTIL_FP_FUNC

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

//! containing endpoints
template <arithm_c FP>
CEXP bool is_in_middle(FP l, FP mid, FP r) { return is_eq(l, mid) || is_eq(r, mid) || ((l < mid) ^ (r < mid)); }

//! containing endpoints
template <class FP>
CEXP bool is_intersect(FP l1, FP r1, FP l2, FP r2) {
  if (l1 > r1) swap(l1, r1);
  if (l2 > r2) swap(l2, r2);
  return !(is_lt(r1, l2) || is_lt(r2, l1));
}

}  // namespace tifa_libs

#endif