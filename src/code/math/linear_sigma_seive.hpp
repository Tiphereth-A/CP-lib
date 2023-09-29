#ifndef TIFA_LIBS_MATH_LINEAR_SIGMA_SEIVE
#define TIFA_LIBS_MATH_LINEAR_SIGMA_SEIVE

#include "linear_seive.hpp"

namespace tifa_libs::math {

inline vec<u64> linear_sigma_seive(u32 n) {
  vec<u64> pw(n), sigma(n);
  sigma[1] = 1;
  linear_seive(
    n,
    [&](u32 p) {
      pw[p] = (u64)p * p;
      sigma[p] = p + 1;
    },
    [&](u32 i, u32 j) {
      pw[i * j] = (u64)j * j;
      sigma[i * j] = sigma[i] * (j + 1);
    },
    [&](u32 i, u32 j) { sigma[i * j] = sigma[i] * ((pw[i * j] = pw[i] * j) - 1) / (pw[i] - 1); });
  return sigma;
}

}  // namespace tifa_libs::math

#endif