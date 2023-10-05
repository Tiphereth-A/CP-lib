#ifndef TIFA_LIBS_MATH_LINEAR_MU_SEIVE
#define TIFA_LIBS_MATH_LINEAR_MU_SEIVE

#include "linear_seive.hpp"

namespace tifa_libs::math {

inline vec<i32> linear_mpf_seive(u32 n) {
  vec<i32> mu(n);
  mu[1] = 1;
  linear_seive(
      n,
      [&](u32 p) { mu[p] = -1; },
      [&](u32 i, u32 j) { mu[i * j] = -mu[i]; },
      []([[maybe_unused]] u32 i, [[maybe_unused]] u32 j) {});
  return mu;
}

}  // namespace tifa_libs::math

#endif