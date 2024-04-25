#ifndef TIFALIBS_STR_LCPF_HASH
#define TIFALIBS_STR_LCPF_HASH

#include "../util/util.hpp"

namespace tifa_libs::str {

// @return length of longest common prefix of suffixes a[i, a.size()) and b[j, b.size())
template <class hashstr_t>
CEXP u32 lcpf_hash(hashstr_t CR a, hashstr_t CR b, u32 i, u32 j, u32 lmax = 0) {
  if (!lmax) lmax = (u32)max(a.size(), b.size());
  u32 l = 0, r = min({lmax, a.size() - i, b.size() - j}) + 1;
  while (l + 1 < r) {
    u32 m = (l + r) / 2;
    (a.get(i, m) == b.get(j, m) ? l : r) = m;
  }
  return l;
}

}  // namespace tifa_libs::str

#endif