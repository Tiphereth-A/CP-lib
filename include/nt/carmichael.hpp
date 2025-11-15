#ifndef TIFALIBS_MATH_CARMICHAEL
#define TIFALIBS_MATH_CARMICHAEL

#include "../math/qpow.hpp"
#include "lcm.hpp"
#include "pfactors.hpp"

namespace tifa_libs::math {

inline u64 carmichael(spn<std::pair<u64, u32>> pf_exp) NE {
  u64 ans = 1;
  for (auto CR[p, e] : pf_exp) ans = lcm(ans, (p - 1) * qpow(p, e - (p == 2 && e >= 3) - 1));
  return ans;
}
inline u64 carmichael(u64 n) NE { return carmichael(pf_exp(n)); }

}  // namespace tifa_libs::math

#endif