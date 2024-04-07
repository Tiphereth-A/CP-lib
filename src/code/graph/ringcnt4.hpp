#ifndef TIFALIBS_GRAPH_RINGCNT4
#define TIFALIBS_GRAPH_RINGCNT4

#include "alist.hpp"

namespace tifa_libs::graph {
namespace ringcnt4_impl_ {
template <bool with_deg>
constexpr u64 run(alist<with_deg> const& dg, alist<with_deg> const& dgv) {
  u64 ans = 0;
  u32 n = (u32)dg.g.size();
  vecu64 cnt1(n), cnt2(n);
  for (u32 u = 0; u < n; ++u) {
    for (u32 v : dg.g[u])
      for (u32 w : dg.g[v]) ++cnt1[w];
    for (u32 v : dgv.g[u])
      for (u32 w : dg.g[v])
        if (w != u) ++cnt2[w];
    for (u32 v : dg.g[u])
      for (u32 w : dg.g[v]) {
        ans += cnt1[w] * (cnt1[w] - 1) + cnt1[w] * cnt2[w] * 2;
        cnt1[w] = 0;
      }
    for (u32 v : dgv.g[u])
      for (u32 w : dg.g[v])
        if (w != u) {
          ans += cnt2[w] * (cnt2[w] - 1) / 2;
          cnt2[w] = 0;
        }
  }
  return ans / 2;
}
}  // namespace ringcnt4_impl_

//! should be simple undirected graph
template <bool with_deg>
constexpr u64 ringcnt4(alist<with_deg> const& fg) {
  auto&& g = fg.g;
  u32 n = (u32)g.size();
  alist dg(n), dgv(n);
  for (u32 u = 0; u < n; ++u)
    for (u32 v : g[u]) (std::make_pair(g[u].size(), u) < std::make_pair(g[v].size(), v) ? dg : dgv).add_arc(u, v);
  return ringcnt4_impl_::run(dg, dgv);
}

}  // namespace tifa_libs::graph

#endif