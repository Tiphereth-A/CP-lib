#ifndef TIFALIBS_MATH_KAHAN
#define TIFALIBS_MATH_KAHAN

#include "../util/util.hpp"

namespace tifa_libs::math {

template <std::floating_point FP>
class kahan {
  FP sum, c;

 public:
  CEXP kahan(FP val = 0) : sum(val), c(0) {}

  CEXP kahan& operator+=(FP x) {
    FP y = x - c;
    volatile FP t = sum + y, z = t - sum;
    c = z - y, sum = t;
    return *this;
  }
  CEXP operator FP() const { return sum; }
};

}  // namespace tifa_libs::math

#endif