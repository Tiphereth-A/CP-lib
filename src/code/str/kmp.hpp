#ifndef TIFALIBS_STR_KMP
#define TIFALIBS_STR_KMP

#include "../util/util.hpp"

namespace tifa_libs::str {

// @return nxt of pattern
inline vec<i32> kmp_nxt(strnv pattern) {
  i32 n = (i32)pattern.size();
  vec<i32> nxt((u32)n);
  i32 i, j;
#pragma GCC diagnostic ignored "-Wsign-conversion"
  for (nxt[0] = j = -1, i = 1; i < n; nxt[i++] = j) {
    while (~j && pattern[j + 1] != pattern[i]) j = nxt[j];
    if (pattern[j + 1] == pattern[i]) ++j;
  }
#pragma GCC diagnostic warning "-Wsign-conversion"
  return nxt;
}

// find pattern in text
// @return matched position in s
inline vecu kmp(strnv pattern, strnv text) {
  vec<i32> nxt = kmp_nxt(pattern);
  vecu ret;
  i32 n = (i32)pattern.size(), m = (i32)text.size(), i, j;
#pragma GCC diagnostic ignored "-Wsign-conversion"
  for (j = -1, i = 0; i < m; ++i) {
    while (~j && pattern[j + 1] != text[i]) j = nxt[j];
    if (pattern[j + 1] == text[i]) ++j;
    if (j == n - 1) ret.push_back(i - n + 1), j = nxt[j];
  }
#pragma GCC diagnostic warning "-Wsign-conversion"
  return ret;
}

}  // namespace tifa_libs::str

#endif