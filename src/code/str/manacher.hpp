#ifndef TIFA_LIBS_STR_MANACHER
#define TIFA_LIBS_STR_MANACHER

#include "../util/util.hpp"

namespace tifa_libs::str {

inline vec<size_t> manacher(std::string_view t) {
  std::string s{'\001', '\002'};
  for (char c : t) (s += c) += '\002';
  s += '\003';
  vec<size_t> p(s.size());
  for (size_t i = 1, j = 0; i + 1 < s.size(); ++i) {
    if (j + p[j] >= i) p[i] = std::min(j + p[j] - i, p[2 * j - i]);
    while (s[i - p[i]] == s[i + p[i]]) ++p[i];
    if (i + p[i] > j + p[j]) j = i;
  }
  return vec<size_t>(p.begin() + 1, p.end() - 1);
}

}  // namespace tifa_libs::str

#endif