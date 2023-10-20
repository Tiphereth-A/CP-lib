#ifndef TIFA_LIBS_MATH_LINEAR_TAU_SEIVE
#define TIFA_LIBS_MATH_LINEAR_TAU_SEIVE

#include "linear_seive.hpp"

namespace tifa_libs::math {

inline vec<u64> linear_tau_seive(u32 n) {
  vec<u32> pc(n, 1);
  vec<u64> tau(n);
  tau[1] = 1;
  linear_seive(
      n,
      [&](u32 p) { tau[p] = 2; },
      [&](u32 i, u32 j) { tau[i * j] = tau[i] * 2; },
      [&](u32 i, u32 j) { tau[i * j] = tau[i] + tau[i] / (pc[i * j] = pc[i] + 1); });
  return tau;
}

}  // namespace tifa_libs::math

#endif