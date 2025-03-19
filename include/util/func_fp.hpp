#ifndef TIFALIBS_UTIL_FUNC_FP
#define TIFALIBS_UTIL_FUNC_FP

#include "consts.hpp"
#include "traits_math.hpp"

namespace tifa_libs {

template <sint_c T>
CEXP int sgn(T x) NE { return (!!x) | (x >> (sizeof(T) * 8 - 1)); }
CEXP int sgn(uint_c auto x) NE { return !!x; }
template <std::floating_point FP>
CEXP int sgn(FP x) NE { return (x > eps_v<FP>)-(x < -eps_v<FP>); }

template <class FP>
CEXP bool is_neg(FP x) NE { return sgn(x) < 0; }
template <class FP>
CEXP bool is_zero(FP x) NE { return !sgn(x); }
template <class FP>
CEXP bool is_pos(FP x) NE { return sgn(x) > 0; }

CEXP int comp(sint_c auto l, sint_c auto r) NE { return sgn(l - r); }
CEXP int comp(uint_c auto l, uint_c auto r) NE { return (!!(l - r)) | -(l < r); }
template <std::floating_point FP>
CEXP int comp(FP l, FP r) NE { return sgn((l - r) / max({abs(l), abs(r), FP(1)})); }

template <class FP>
CEXP bool is_lt(FP l, FP r) NE { return comp(l, r) < 0; }
template <class FP>
CEXP bool is_eq(FP l, FP r) NE { return !comp(l, r); }
template <class FP>
CEXP bool is_gt(FP l, FP r) NE { return comp(l, r) > 0; }

//! containing endpoints
CEXP bool is_in_middle(arithm_c auto l, arithm_c auto mid, arithm_c auto r) NE { return is_eq(l, mid) || is_eq(r, mid) || ((l < mid) ^ (r < mid)); }

//! containing endpoints
template <class FP>
CEXP bool is_intersect(FP l1, FP r1, FP l2, FP r2) NE {
  if (l1 > r1) swap(l1, r1);
  if (l2 > r2) swap(l2, r2);
  return !(is_lt(r1, l2) || is_lt(r2, l1));
}

}  // namespace tifa_libs

#endif