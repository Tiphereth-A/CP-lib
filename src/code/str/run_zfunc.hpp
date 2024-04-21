#ifndef TIFALIBS_STR_RUN_ZFUNC
#define TIFALIBS_STR_RUN_ZFUNC

#include "z_func.hpp"

namespace tifa_libs::str {

// @return {p, l, r}, uniqued
constexpr vec<pt3<u32>> run_zfunc(strn const& s) {
  vec<pt3<u32>> rs;

  auto rec = [&](auto&& rec, u32 l, u32 r) -> void {
    if (r - l <= 1) return;
    u32 m = (l + r) / 2;
    rec(rec, l, m), rec(rec, m, r);
    auto f = [&](bool rev) {
      auto t = s.substr(l, r - l);
      if (rev) std::ranges::reverse(t), m = l + r - m;
      u32 len = r - l, mid = m - l;
      strn tl = t.substr(0, mid), tr = t.substr(mid, len - mid) + t;
      std::ranges::reverse(tl);
      auto zl = z_func(tl), zr = z_func(tr);
      zl.push_back(0);
      for (u32 k = 1; k <= mid; ++k) {
        u32 li = m - k - zl[k], ri = m + std::min(r - m, zr[len - k]);
        if (rev) std::swap(li = l + r - li, ri = l + r - ri);
        if (ri - li < 2 * k) continue;
        if (li > 0 && s[li - 1] == s[li - 1 + k]) continue;
        if (ri < s.size() && s[ri] == s[ri - k]) continue;
        rs.emplace_back(li, ri, k);
      }
    };
    f(0), f(1);
  };
  rec(rec, 0, (u32)s.size());
  std::ranges::sort(rs);
  vec<pt3<u32>> runs;
  for (u32 i = 0; i < rs.size(); ++i) {
    auto [l, r, t] = rs[i];
    if (i && l == get<0>(rs[i - 1]) && r == get<1>(rs[i - 1])) continue;
    runs.emplace_back(t, l, r);
  }
  std::ranges::sort(runs);
  return runs;
}

}  // namespace tifa_libs::str

#endif