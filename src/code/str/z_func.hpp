#ifndef TIFALIBS_STR_Z_FUNC
#define TIFALIBS_STR_Z_FUNC

#include "../util/util.hpp"

namespace tifa_libs::str {

CEXP vecu z_func(strnv s) {
  const u32 n = (u32)s.size();
  vecu z(n);
  for (u32 i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r && z[i - l] < r - i + 1) z[i] = z[i - l];
    else {
      if (i <= r) z[i] = r - i + 1;
      while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
    }
    if (i + z[i] - 1 > r) r = i + z[l = i] - 1;
  }
  return z[0] = n, z;
}

}  // namespace tifa_libs::str

#endif