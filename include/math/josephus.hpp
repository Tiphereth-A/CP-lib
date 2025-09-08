#ifndef TIFALIBS_MATH_JOSEPHUS
#define TIFALIBS_MATH_JOSEPHUS

#include "../util/alias_num.hpp"

namespace tifa_libs::math {
namespace josephus_impl_ {
// $O(m)$
CEXP u64 j1(u64 n, u64 k, u64 m) NE {
  if (m == 1) return (k - 1) % n;
  return (j1(n - 1, k, m - 1) + k) % n;
}
// $O(k\log n)$
CEXP u64 j2(u64 n, u64 k, u64 m) NE {
  if (k == 1) return m - 1;
  u64 n2 = n - m + 1, ret = j1(n2, k, 1);
  --m;
  while (m)
    if (u64 _ = (n2 - ret) / (k - 1); m <= _) return (ret + m * k) % (n2 + m);
    else ret = (((ret + _ * k) % (n2 + _)) + k) % (n2 + _ + 1), n2 += _ + 1, m -= _ + 1;
  return ret;
}
}  // namespace josephus_impl_

//! 0-based
// @return $m$-th executed person in Josephus problem
//         with total_people = n, start_point = 0, skipped_number = k
CEXP u64 Josephus(u64 n, u64 k, u64 m) NE {
  assert(m && k && m <= n);
  retif_((m < k * (u32)std::bit_width(n)), josephus_impl_::j1(n, k, m), josephus_impl_::j2(n, k, m));
}

}  // namespace tifa_libs::math

#endif