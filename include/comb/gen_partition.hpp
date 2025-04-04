#ifndef TIFALIBS_COMB_GEN_PARTITION
#define TIFALIBS_COMB_GEN_PARTITION

#include "../poly/inv_fps.hpp"

namespace tifa_libs::math {

// partition[i] = p(i), i=0,1,...,n
template <class poly>
CEXP poly gen_partition(u32 n) NE {
  if (n == 0) return poly{1};
  poly p(n + 1);
  p[0] = 1;
  for (u64 k = 1, k1, k2; k <= n; ++k) {
    if ((k2 = k * (3 * k - 1) / 2) > n) break;
    if ((k1 = k * (3 * k + 1) / 2) <= n) p[(u32)k1] += ((k & 1) ? -1 : 1);
    if (k2 <= n) p[(u32)k2] += ((k & 1) ? -1 : 1);
  }
  return inv_fps(p);
}

}  // namespace tifa_libs::math

#endif