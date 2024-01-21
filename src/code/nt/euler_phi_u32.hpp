#ifndef TIFALIBS_MATH_EULER_PHI_U32
#define TIFALIBS_MATH_EULER_PHI_U32

#include "../math/isqrt.hpp"

namespace tifa_libs::math {

constexpr u32 euler_phi_u32(u32 n) {
  u32 ans = n;
  for (u32 i = 2, ed = isqrt(n); i <= ed; ++i)
    if (!(n % i)) {
      ans = ans / i * (i - 1);
      while (!(n % i)) n /= i;
      ed = isqrt(n);
    }
  if (n > 1) ans = ans / n * (n - 1);
  return ans;
}

}  // namespace tifa_libs::math

#endif