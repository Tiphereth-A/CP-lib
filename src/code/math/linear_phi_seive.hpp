#ifndef TIFA_LIBS_MATH_LINEAR_PHI_SEIVE
#define TIFA_LIBS_MATH_LINEAR_PHI_SEIVE

#include "../util/util.hpp"

#include "linear_seive.hpp"

namespace tifa_libs::math {

inline vec<u32> linear_phi_seive(u32 n) {
  vec<u32> phi(n);
  phi[1] = 1;
  linear_seive(
    n,
    [&](u32 p) { phi[p] = p - 1; },
    [&](u32 i, u32 j) { phi[i * j] = phi[i] * (j - 1); },
    [&](u32 i, u32 j) { phi[i * j] = phi[i] * j; });
  return phi;
}

}  // namespace tifa_libs::math

#endif