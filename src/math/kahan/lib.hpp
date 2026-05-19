#pragma once

#include "../../util/util/lib.hpp"

namespace tifa_libs {

template <std::floating_point FP>
class kahan_fp {
  FP sum, c{0};

 public:
  CEXP kahan_fp(FP val = 0) NE : sum{val} {}

  CEXP kahan_fp& operator+=(FP x) NE {
    const FP y = x - c;
    volatile FP t = sum + y, z = t - sum;
    c = z - y, sum = t;
    return *this;
  }
  CEXP operator FP() CNE { return sum; }
};
template <class FP>
using kahan = std::conditional_t<std::floating_point<FP>, kahan_fp<FP>, FP>;

}  // namespace tifa_libs
