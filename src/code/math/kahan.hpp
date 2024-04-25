#ifndef TIFALIBS_MATH_KAHAN
#define TIFALIBS_MATH_KAHAN

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class FP>
CEXP FP kahan(vec<FP> CR vec) {
  FP sum = 0, c = 0;
  for (auto x : vec) {
    FP y = x - c, t = sum + y;
    c = (t - sum) - y;
    sum = t;
  }
  return sum;
}

}  // namespace tifa_libs::math

#endif