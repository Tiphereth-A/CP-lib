#ifndef TIFALIBS_STR_LYNDON
#define TIFALIBS_STR_LYNDON

#include "../util/util.hpp"

namespace tifa_libs::str {

inline vec<u32> duval(std::string_view str) {
  const u32 n = (u32)str.size();
  vec<u32> res{0};
  while (res.back() != n) {
    u32 l = 1;
    for (u32 i = res.back() + 1; i < n + 1; ++i)
      if (i == n || str[i] < str[i - l]) {
        for (u32 j = res.back() + l; j < i + 1; j += l) res.push_back(j);
        break;
      } else if (str[i - l] < str[i]) l = i + 1 - res.back();
  }
  return res;
}

}  // namespace tifa_libs::str

#endif