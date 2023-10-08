#ifndef TIFA_LIBS_UTIL_FP_RANGE_IS_IN_MIDDLE
#define TIFA_LIBS_UTIL_FP_RANGE_IS_IN_MIDDLE

#include "fp_comp.hpp"

namespace tifa_libs {

//! containing endpoints
template <class FP>
constexpr bool is_in_middle(FP l, FP mid, FP r) { return is_eq(l, mid) || is_eq(r, mid) || ((l < mid) ^ (r < mid)); }

}  // namespace tifa_libs

#endif