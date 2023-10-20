#ifndef TIFA_LIBS_STR_Z_ALGO
#define TIFA_LIBS_STR_Z_ALGO

#include "../util/util.hpp"

namespace tifa_libs::str {

inline vec<usz> z_function(std::string_view s) {
  usz n = s.size();
  vec<usz> z(n);
  for (usz i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r && z[i - l] < r - i + 1) z[i] = z[i - l];
    else {
      if (i <= r) z[i] = r - i + 1;
      while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
    }
    if (i + z[i] - 1 > r) r = i + z[l = i] - 1;
  }
  z[0] = n;
  return z;
}

}  // namespace tifa_libs::str

#endif