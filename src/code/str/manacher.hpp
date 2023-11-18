#ifndef TIFA_LIBS_STR_MANACHER
#define TIFA_LIBS_STR_MANACHER

#include "../util/util.hpp"

namespace tifa_libs::str {

inline vec<u32> manacher(std::string_view t) {
  std::string s{'\001', '\002'};
  for (char c : t) (s += c) += '\002';
  s += '\003';
  vec<u32> p(s.size());
  for (u32 i = 1, j = 0; i + 1 < s.size(); ++i) {
    if (j + p[j] >= i) p[i] = std::min(j + p[j] - i, p[2 * j - i]);
    while (s[i - p[i]] == s[i + p[i]]) ++p[i];
    if (i + p[i] > j + p[j]) j = i;
  }
  for (auto &i : p) --i;
  return vec<u32>(p.begin() + 2, p.end() - 2);
}

}  // namespace tifa_libs::str

#endif