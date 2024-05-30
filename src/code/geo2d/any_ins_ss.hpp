#ifndef TIFALIBS_GEO2D_ANY_INS_SS
#define TIFALIBS_GEO2D_ANY_INS_SS

#include "ins_ll.hpp"
#include "is_ins_sl.hpp"

namespace tifa_libs::geo {

// judge if any two segments are intersected
template <class FP>
CEXP bool any_ins_Ss(vec<line<FP>> CR ss) {
  if (ss.empty()) return false;
  using seq_t = std::tuple<FP, int, line<FP>>;
  const auto seqcmp = [](seq_t CR u, seq_t CR v) {
    auto CR[u0, u1, u2] = u;
    auto CR[v0, v1, v2] = v;
    if (is_eq(u0, v0)) return u1 == v1 ? u2 < v2 : u1 < v1;
    return is_lt(u0, v0);
  };
  vec<seq_t> seq;
  for (auto seg : ss) {
    if (is_gt(seg.l.x, seg.r.x)) swap(seg.l, seg.r);
    seq.emplace_back(seg.l.x, 0, seg), seq.emplace_back(seg.r.x, 1, seg);
  }
  std::ranges::sort(seq, seqcmp);
  FP x_now;
  auto cmp = [&](line<FP> CR u, line<FP> CR v) {
    if (is_eq(u.l.x, u.r.x) || is_eq(v.l.x, v.r.x)) return is_lt(u.l.y, v.l.y);
    return is_lt(((x_now - u.l.x) * (u.r.y - u.l.y) + u.l.y * (u.r.x - u.l.x)) * (v.r.x - v.l.x), ((x_now - v.l.x) * (v.r.y - v.l.y) + v.l.y * (v.r.x - v.l.x)) * (u.r.x - u.l.x));
  };
  std::multiset<line<FP>, decltype(cmp)> s{cmp};
  for (auto CR[x, o, seg] : seq) {
    x_now = x;
    auto it = s.lower_bound(seg);
    if (!o) {
      if (it != s.end() && is_ins_SL(seg, *it)) return 1;
      if (it != s.begin() && is_ins_SL(seg, *prev(it))) return 1;
      s.insert(seg);
    } else {
      if (next(it) != s.end() && it != s.begin() && is_ins_LL(*prev(it), *next(it))) return 1;
      s.erase(it);
    }
  }
  return 0;
}

}  // namespace tifa_libs::geo

#endif