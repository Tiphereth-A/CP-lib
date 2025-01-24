#ifndef TIFALIBS_STR_SUFFIX_ARRAY
#define TIFALIBS_STR_SUFFIX_ARRAY

#include "../util/traits.hpp"

namespace tifa_libs::str {

template <iterable_c T = strn>
class suffixarray {
  T s;

 public:
  vecu sa, rk, height;

  // s must start from 1
  CEXPE suffixarray(cT_(T) s_) NE : s(s_), sa(s.size()), rk(s.size()) {
    const u32 n = u32(s.size() - 1);
    u32 m = 0, p;
    for (auto x : s_) m = max(m, u32(x));
    vecu oldrk(n + n + 1), id(n + 1), cnt(m + 1, 0);
    flt_ (u32, i, 1, n + 1) ++cnt[rk[i] = u32(s[i])];
    flt_ (u32, i, 1, m + 1) cnt[i] += cnt[i - 1];
    for (u32 i = n; i >= 1; --i) sa[cnt[rk[i]]--] = i;
    for (u32 w = 1;; w *= 2, m = p) {
      p = 0;
      for (u32 i = n; i > n - w; --i) id[++p] = i;
      flt_ (u32, i, 1, n + 1)
        if (sa[i] > w) id[++p] = sa[i] - w;
      cnt = vecu(m + 1, 0);
      flt_ (u32, i, 1, n + 1) ++cnt[rk[id[i]]];
      flt_ (u32, i, 1, m + 1) cnt[i] += cnt[i - 1];
      for (u32 i = n; i >= 1; --i) sa[cnt[rk[id[i]]]--] = id[i];
      std::ranges::copy(rk, oldrk.begin()), p = 0;
      flt_ (u32, i, 1, n + 1) {
        u32 x = sa[i], y = sa[i - 1];
        rk[x] = oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w] ? p : ++p;
      }
      if (p == n) break;
    }
  }

  CEXP void get_height() NE {
    const u32 n = u32(s.size() - 1);
    height = vecu(n + 1);
    for (u32 i = 1, k = 0; i <= n; ++i) {
      if (rk[i] == 1) continue;
      if (k) --k;
      while (i + k <= n && s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
      height[rk[i]] = k;
    }
  }
  // s.substr(begs) := s[begs..s.size() - 1]
  // -1:  t > s.substr
  // 0 :  t == s.substr
  // 1 :  t < s.substr, t is a prefix of s.substr
  // 2 :  t < s.substr, t isn't prefix of s.substr
  CEXP i32 compare_substr(T t, u32 begs = 1, u32 begt = 1) CNE {
    while (begs < s.size() && begt < t.size()) {
      if (t[begt] > s[begs]) return -1;
      if (t[begt] < s[begs]) return 2;
      ++begs, ++begt;
    }
    return begs == s.size() && begt == t.size() ? 0 : (begt >= t.size() ? 1 : -1);
  }
  // the smallest rank of suffix that is greater than or equal t
  CEXP u32 lower_bound(T t) CNE {
    u32 l = 1, r = u32(s.size() - 1), ret = u32(s.size());
    while (r >= l) {
      const u32 m = l + (r - l) / 2;
      if (compare_substr(t, sa[m]) < 0) l = m + 1;
      else r = m - 1, ret = m;
    }
    return ret;
  }
  // the smallest rank of suffix that is greater than t and t isn't prefix of that
  CEXP u32 upper_bound(T t) CNE {
    u32 l = 1, r = u32(s.size() - 1), ret = u32(s.size());
    while (r >= l)
      if (const u32 m = l + (r - l) / 2; compare_substr(t, sa[m]) <= 1) l = m + 1;
      else r = m - 1, ret = m;
    return ret;
  }
  CEXP u32 frequency(T t) CNE { return upper_bound(t) - lower_bound(t); }
};

}  // namespace tifa_libs::str

#endif