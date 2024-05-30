#ifndef TIFALIBS_GEO2D_AUNION_POS
#define TIFALIBS_GEO2D_AUNION_POS

#include "ins_ll.hpp"
#include "is_ins_sl.hpp"
#include "polygon.hpp"

namespace tifa_libs::geo {

// @return ans, which ans[i] means area covered at least i+1 times
template <std::floating_point FP>
CEXP vec<FP> aunion_Pos(vec<polygon<FP>> CR pos) {
  u32 n = (u32)pos.size();
  vvecpt<point<FP>> segs(n);
  auto chk = [](point<FP> CR u, line<FP> CR e) { return !((u < e.l && u < e.r) || (u > e.l && u > e.r)); };
  auto cut = [&](line<FP> CR e, u32 i) {
    const line<FP> le{e.l, e.r};
    vecp<point<FP>, int> evt;
    evt.emplace_back(e.l, 0), evt.emplace_back(e.r, 0);
    flt_ (u32, j, 0, n) {
      if (i == j) continue;
      auto CR pj = pos[j];
      flt_ (u32, k, 0, pj.size()) {
        const line<FP> s{pj[k], pj[pj.next(k)]};
        if (!le.toleft(s.l) && !le.toleft(s.r)) evt.emplace_back(s.l, 0), evt.emplace_back(s.r, 0);
        else if (!is_ins_SL(s, le)) {
          if (point<FP> u = ins_LL(le, s); le.toleft(s.l) < 0 && le.toleft(s.r) >= 0) evt.emplace_back(u, -1);
          else if (le.toleft(s.l) >= 0 && le.toleft(s.r) < 0) evt.emplace_back(u, 1);
        }
      }
    }
    std::ranges::sort(evt);
    if (e.l > e.r) std::ranges::reverse(evt);
    int sum = 0;
    flt_ (u32, i, 0, (u32)evt.size()) {
      sum += evt[i].second;
      point<FP> u = evt[i].first, v = evt[i + 1].first;
      if (!(u == v) && chk(u, e) && chk(v, e)) segs[(u32)sum].emplace_back(u, v);
      if (v == e.r) break;
    }
  };
  flt_ (u32, i, 0, (u32)pos.size()) {
    auto CR pi = pos[i];
    flt_ (u32, k, 0, pi.size()) cut({pi[k], pi[pi.next(k)]}, i);
  }
  vec<FP> ans(n);
  flt_ (u32, i, 0, n) {
    std::ranges::sort(segs[i]);
    FP sum = 0;
    u32 cnt = 0;
    flt_ (u32, j, 0, (u32)segs[i].size()) {
      if (j > 0 && segs[i][j] == segs[i][j - 1]) segs[i + (++cnt)].push_back(segs[i][j]);
      else cnt = 0, sum += segs[i][j].first ^ segs[i][j].second;
    }
    ans[i] = sum / 2;
  }
  return ans;
}

}  // namespace tifa_libs::geo

#endif