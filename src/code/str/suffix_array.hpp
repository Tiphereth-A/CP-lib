#ifndef TIFA_LIBS_STR_SUFFIX_ARRAY
#define TIFA_LIBS_STR_SUFFIX_ARRAY

#include "../util/util.hpp"

namespace tifa_libs::str {

template <u32 MAXCHAR = u32('z')>
// s must start from 1
inline ptt<vec<usz>> suffixsort(std::string s) {
  usz n = s.size() - 1, m = MAXCHAR, p;
  vec<usz> sa(n + 1), rk(n + 1), oldrk(n + n + 1), id(n + 1), cnt(m + 1, 0);
  for (usz i = 1; i <= n; ++i) ++cnt[rk[i] = usz(s[i])];
  for (usz i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
  for (usz i = n; i >= 1; --i) sa[cnt[rk[i]]--] = i;

  for (usz w = 1;; w *= 2, m = p) {
    p = 0;
    for (usz i = n; i > n - w; --i) id[++p] = i;
    for (usz i = 1; i <= n; ++i)
      if (sa[i] > w) id[++p] = sa[i] - w;

    cnt = vec<usz>(m + 1, 0);
    for (usz i = 1; i <= n; ++i) ++cnt[rk[id[i]]];
    for (usz i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
    for (usz i = n; i >= 1; --i) sa[cnt[rk[id[i]]]--] = id[i];
    std::copy(rk.begin(), rk.end(), oldrk.begin());
    p = 0;
    for (usz i = 1; i <= n; ++i) {
      usz x = sa[i], y = sa[i - 1];
      rk[x] = oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w] ? p : ++p;
    }
    if (p == n) break;
  }
  return {sa, rk};
}

inline pt3<vec<usz>> suffixsort_height(std::string s) {
  auto [sa, rk] = suffixsort(s);
  usz n = s.size() - 1;
  vec<usz> height(n + 1);
  for (usz i = 1, k = 0; i <= n; ++i) {
    if (rk[i] == 1) continue;
    if (k) --k;
    while (i + k <= n && s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
    height[rk[i]] = k;
  }
  return {sa, rk, height};
}

}  // namespace tifa_libs::str

#endif