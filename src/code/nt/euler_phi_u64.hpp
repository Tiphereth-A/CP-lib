#ifndef TIFALIBS_MATH_EULER_PHI_U64
#define TIFALIBS_MATH_EULER_PHI_U64

#include "euler_phi_u32.hpp"
#include "pfactors.hpp"

namespace tifa_libs::math {

inline u64 euler_phi_u64(u64 n) NE {
  if (n <= (u64)-1_u32) return euler_phi_u32((u32)n);
  for (const auto pf = pfactors(n); auto CR p : pf) n = n / p * (p - 1);
  return n;
}

}  // namespace tifa_libs::math

#endif