#ifndef TIFALIBS_STR_LYNDON
#define TIFALIBS_STR_LYNDON

#include "../util/alias_others.hpp"

namespace tifa_libs::str {

CEXP vecu duval(strnv s) NE {
  const u32 n = (u32)s.size();
  vecu res{0};
  while (res.back() != n) {
    u32 l = 1;
    flt_ (u32, i, res.back() + 1, n + 1)
      if (i == n || s[i] < s[i - l]) {
        for (u32 j = res.back() + l; j < i + 1; j += l) res.push_back(j);
        break;
      } else if (s[i - l] < s[i]) l = i + 1 - res.back();
  }
  return res;
}

}  // namespace tifa_libs::str

#endif