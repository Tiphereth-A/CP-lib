#ifndef TIFA_LIBS_MATH_KAHAN
#define TIFA_LIBS_MATH_KAHAN

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class FP>
FP kahan(vec<FP> const &vec) {
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