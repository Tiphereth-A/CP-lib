#ifndef TIFA_LIBS_UTIL_FP_RANGE_IS_INTERSECT
#define TIFA_LIBS_UTIL_FP_RANGE_IS_INTERSECT

#include "fp_comp.hpp"

namespace tifa_libs {

//! containing endpoints
template <class FP>
constexpr bool is_intersect(FP l1, FP r1, FP l2, FP r2) {
  if (l1 > r1) std::swap(l1, r1);
  if (l2 > r2) std::swap(l2, r2);
  return !(is_lt(r1, l2) || is_lt(r2, l1));
}

}  // namespace tifa_libs

#endif