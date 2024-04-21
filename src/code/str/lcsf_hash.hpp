#ifndef TIFALIBS_STR_LCSF_HASH
#define TIFALIBS_STR_LCSF_HASH

#include "../util/util.hpp"

namespace tifa_libs::str {

// @return length of longest common suffix of prefixes a[0, i) and b[0, j)
template <class hashstr_t>
constexpr u32 lcsf_hash(hashstr_t const& a, hashstr_t const& b, u32 i, u32 j, u32 lmax = 0) {
  if (!lmax) lmax = (u32)std::max(a.size(), b.size());
  u32 l = 0, r = std::min({lmax, i, j}) + 1;
  while (l + 1 < r) {
    u32 m = (l + r) / 2;
    (a.get(i - m, m) == b.get(j - m, m) ? l : r) = m;
  }
  return l;
}

}  // namespace tifa_libs::str

#endif