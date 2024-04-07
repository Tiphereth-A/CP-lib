#ifndef TIFALIBS_UTIL_JOSEPHUS
#define TIFALIBS_UTIL_JOSEPHUS

#include "../util/util.hpp"

namespace tifa_libs::util {

namespace josephus_impl_ {
// $O(m)$
constexpr u64 j1(u64 n, u64 k, u64 m) {
  if (m == 1) return (k - 1) % n;
  else return (j1(n - 1, k, m - 1) + k) % n;
}
// $O(k\log n)$
constexpr u64 j2(u64 n, u64 k, u64 m) {
  if (k == 1) return m - 1;
  u64 n2 = n - m + 1, ret = j1(n2, k, 1);
  --m;
  while (m) {
    u64 _ = (n2 - ret) / (k - 1);
    if (m <= _) return (ret + m * k) % (n2 + m);
    else {
      ret = (((ret + _ * k) % (n2 + _)) + k) % (n2 + _ + 1);
      n2 += _ + 1, m -= _ + 1;
    }
  }
  return ret;
}
}  // namespace josephus_impl_

//! 0-based
// @return $m$-th executed person in Josephus problem
//         with total_people = n, start_point = 0, skipped_number = k
constexpr u64 Josephus(u64 n, u64 k, u64 m) {
  assert(m && k && m <= n);
  return m < k * (u32)std::bit_width(n) ? josephus_impl_::j1(n, k, m) : josephus_impl_::j2(n, k, m);
}

}  // namespace tifa_libs::util

#endif