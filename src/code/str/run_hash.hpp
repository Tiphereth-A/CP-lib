#ifndef TIFALIBS_STR_RUN_HASH
#define TIFALIBS_STR_RUN_HASH

#include "../edh/discretization.hpp"
#include "lcpf_hash.hpp"
#include "lcsf_hash.hpp"

namespace tifa_libs::str {

// @return {p, l, r}, uniqued
template <class hashstr_t>
CEXP vec<pt3u> run_hash(strnv s) {
  const u32 n = (u32)s.size();
  vecu st(n + 1);
  vec<pt3u> runs;
  hashstr_t hs;
  hs.set(s);
  flt_ (u32, inv, 0, 2) {
    st[0] = n + 1;
    for (u32 i = n, top = 0, lt = 0; i; --i) {
      while (top) {
        const u32 x = min(st[top] - i, st[top - 1] - st[top]);
        if (lt = s[i - 1] == s[st[top] - 1] ? lcpf_hash(hs, hs, i - 1, st[top] - 1, x) : 0; (lt == x && st[top] - i < st[top - 1] - st[top]) || (lt < x && ((s[i + lt - 1] < s[st[top] + lt - 1]) ^ inv))) --top, lt = 0;
        else break;
      }
      const u32 j = st[top], x = i > 1 && s[i - 2] == s[j - 2] ? lcsf_hash(hs, hs, i - 1, j - 1, j - i) : 0;
      if (st[++top] = i; x < j - i)
        if (u32 y = s[i + lt - 1] == s[j + lt - 1] ? lt + lcpf_hash(hs, hs, i + lt - 1, j + lt - 1, n) : lt;
            x + y >= j - i) runs.emplace_back(j - i, i - x - 1, j + y - 1);
    }
  }
  return uniq(runs);
}

}  // namespace tifa_libs::str

#endif