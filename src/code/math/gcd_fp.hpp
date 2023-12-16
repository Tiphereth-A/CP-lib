#ifndef TIFALIBS_MATH_GCD_FP
#define TIFALIBS_MATH_GCD_FP

#include "../util/util.hpp"

namespace tifa_libs::math {

template <std::floating_point T>
constexpr T gcd_fp(T a, T b, T eps = 1e-2) {
  if ((a = std::abs(a)) < (b = std::abs(b))) std::swap(a, b);
  while (a - b > eps) {
    if (b < eps) return a;
    std::swap(a = std::fmod(a, b), b);
  }
  return a;
}

}  // namespace tifa_libs::math

#endif