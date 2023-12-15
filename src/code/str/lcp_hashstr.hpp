#ifndef TIFALIBS_STR_LCP_HASHSTR
#define TIFALIBS_STR_LCP_HASHSTR

#include "../util/util.hpp"

namespace tifa_libs::str {

template <class hashstr_t>
constexpr u32 lcp_hashstr(hashstr_t const& a, hashstr_t const& b, u32 pos_a, u32 pos_b) {
  u32 l = 0, r = std::min(a.size() - pos_a, b.size() - pos_b) + 1;
  while (l + 1 < r) {
    u32 m = (l + r) / 2;
    (a.get(pos_a, m) == b.get(pos_b, m) ? l : r) = m;
  }
  return l;
}

}  // namespace tifa_libs::str

#endif