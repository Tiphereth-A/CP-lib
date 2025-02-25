#ifndef TIFALIBS_STR_RUN_ZFUNC
#define TIFALIBS_STR_RUN_ZFUNC

#include "z_func.hpp"

namespace tifa_libs::str {

// @return {p, l, r}, uniqued
CEXP vec<pt3u> run_zfunc(strnv s) NE {
  vec<pt3u> rs;

  auto rec = [&](auto&& rec, u32 l, u32 r) NE -> void {
    if (r - l <= 1) return;
    u32 m = (l + r) / 2;
    rec(rec, l, m), rec(rec, m, r);
    auto f = [&](bool rev) NE {
      strn t(s.substr(l, r - l));
      if (rev) reverse(t), m = l + r - m;
      const u32 len = r - l, mid = m - l;
      strn tl = t.substr(0, mid), tr = t.substr(mid, len - mid) + t;
      reverse(tl);
      auto zl = z_func(tl), zr = z_func(tr);
      zl.push_back(0);
      flt_ (u32, k, 1, mid + 1) {
        u32 li = m - k - zl[k], ri = m + min(r - m, zr[len - k]);
        if (rev) swap(li = l + r - li, ri = l + r - ri);
        if (ri - li < 2 * k) continue;
        if (li > 0 && s[li - 1] == s[li - 1 + k]) continue;
        if (ri < s.size() && s[ri] == s[ri - k]) continue;
        rs.emplace_back(li, ri, k);
      }
    };
    f(0), f(1);
  };
  rec(rec, 0, (u32)s.size());
  sort(rs);
  vec<pt3u> runs;
  flt_ (u32, i, 0, (u32)rs.size()) {
    auto [l, r, t] = rs[i];
    if (i && l == rs[i - 1]._0 && r == rs[i - 1]._1) continue;
    runs.emplace_back(t, l, r);
  }
  sort(runs);
  return runs;
}

}  // namespace tifa_libs::str

#endif