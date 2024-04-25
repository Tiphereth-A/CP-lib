#ifndef TIFALIBS_STR_LCS_SA
#define TIFALIBS_STR_LCS_SA

#include "suffix_array.hpp"

namespace tifa_libs::str {

// @return {sl, sr, tl, tr} s.t. s[sl..sr-1] == t[tl..tr-1]
CEXP auto lcs_sa(cT_(strn) s, cT_(strn) t) {
  tifa_libs::str::suffixarray<> sa(" " + s + "#" + t);
  sa.get_height();
  pt3<u32> ans{};
  for (u32 i = 2; i < sa.sa.size(); ++i) {
    if (sa.sa[i - 1] - 1 < s.size() && sa.sa[i] - 1 > s.size()) ans = max(ans, pt3<u32>{sa.height[i], sa.sa[i - 1] - 1, sa.sa[i] - 1});
    if (sa.sa[i] - 1 < s.size() && sa.sa[i - 1] - 1 > s.size()) ans = max(ans, pt3<u32>{sa.height[i], sa.sa[i] - 1, sa.sa[i - 1] - 1});
  }
  auto [l, a, b] = ans;
  b -= s.size() + 1;
  return l ? pt4<u32>{a, a + l, b, b + l} : pt4<u32>{0, 0, 0, 0};
}

}  // namespace tifa_libs::str

#endif