#ifndef TIFALIBS_MATH_EULER_PHI
#define TIFALIBS_MATH_EULER_PHI

#include "pfactors.hpp"

namespace tifa_libs::math {

CEXP u64 euler_phi(u64 n, spn<std::pair<u64, u32>> pf_exp) NE {
  for (auto CR[p, _] : pf_exp) n = n / p * (p - 1);
  return n;
}
CEXP u64 euler_phi(u64 n, spnuu pfactor) NE {
  for (auto CR p : pfactor) n = n / p * (p - 1);
  return n;
}
inline u64 euler_phi(u64 n) NE { return euler_phi(n, pfactors(n)); }

}  // namespace tifa_libs::math

#endif