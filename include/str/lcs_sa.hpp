#ifndef TIFALIBS_STR_LCS_SA
#define TIFALIBS_STR_LCS_SA

#include "suffix_array.hpp"

namespace tifa_libs::str {

// @return {sl, sr, tl, tr} s.t. s[sl..sr-1] == t[tl..tr-1]
CEXP pt4u lcs_sa(strnv s, strnv t) NE {
  tifa_libs::str::suffix_array sa(" "s + s.data() + "#" + t.data());
  sa.get_height();
  pt3u ans{};
  flt_ (u32, i, 2, (u32)sa.sa.size()) {
    if (sa.sa[i - 1] - 1 < s.size() && sa.sa[i] - 1 > s.size()) ans = max(ans, pt3u{sa.height[i], sa.sa[i - 1] - 1, sa.sa[i] - 1});
    if (sa.sa[i] - 1 < s.size() && sa.sa[i - 1] - 1 > s.size()) ans = max(ans, pt3u{sa.height[i], sa.sa[i] - 1, sa.sa[i - 1] - 1});
  }
  auto [l, a, b] = ans;
  b -= s.size() + 1;
  if (l) return {a, a + l, b, b + l};
  return {0, 0, 0, 0};
}

}  // namespace tifa_libs::str

#endif