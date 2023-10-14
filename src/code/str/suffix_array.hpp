#ifndef TIFA_LIBS_STR_SUFFIX_ARRAY
#define TIFA_LIBS_STR_SUFFIX_ARRAY

#include "../util/util.hpp"

namespace tifa_libs::str {

// s must start from 1
inline ptt<vec<size_t>> suffixsort(std::string s) {
  size_t n = s.size() - 1, m = size_t('z'), p;
  vec<size_t> sa(n + 1), rk(n + 1), oldrk(n + n + 1), id(n + 1), cnt(m + 1, 0);
  for (size_t i = 1; i <= n; ++i) ++cnt[rk[i] = size_t(s[i])];
  for (size_t i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
  for (size_t i = n; i >= 1; --i) sa[cnt[rk[i]]--] = i;

  for (size_t w = 1;; w <<= 1, m = p) {
    p = 0;
    for (size_t i = n; i > n - w; --i) id[++p] = i;
    for (size_t i = 1; i <= n; ++i)
      if (sa[i] > w) id[++p] = sa[i] - w;

    cnt = vec<size_t>(m + 1, 0);
    for (size_t i = 1; i <= n; ++i) ++cnt[rk[id[i]]];
    for (size_t i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
    for (size_t i = n; i >= 1; --i) sa[cnt[rk[id[i]]]--] = id[i];
    std::copy(rk.begin(), rk.end(), oldrk.begin());
    p = 0;
    for (size_t i = 1; i <= n; ++i) {
      size_t x = sa[i], y = sa[i - 1];
      rk[x] = oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w] ? p : ++p;
    }
    if (p == n) break;
  }
  return {sa, rk};
}

}  // namespace tifa_libs::str

#endif