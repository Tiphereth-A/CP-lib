#ifndef TIFA_LIBS_GRAPH_RINGCNT4
#define TIFA_LIBS_GRAPH_RINGCNT4

#include "adjlist.hpp"

namespace tifa_libs::graph {

namespace ringcnt4_impl_ {

inline u64 run_(adjlist<> const& dg, adjlist<> const& dgv) {
  u64 ans = 0;
  u32 n = dg.v_size();
  vec<u64> cnt1(n), cnt2(n);
  for (u32 u = 0; u < n; ++u) {
    for (auto [v] : dg[u])
      for (auto [w] : dg[v]) ++cnt1[w];
    for (auto [v] : dgv[u])
      for (auto [w] : dg[v])
        if (w != u) ++cnt2[w];
    for (auto [v] : dg[u])
      for (auto [w] : dg[v]) {
        ans += cnt1[w] * (cnt1[w] - 1) + cnt1[w] * cnt2[w] * 2;
        cnt1[w] = 0;
      }
    for (auto [v] : dgv[u])
      for (auto [w] : dg[v])
        if (w != u) {
          ans += cnt2[w] * (cnt2[w] - 1) / 2;
          cnt2[w] = 0;
        }
  }
  return ans / 2;
}

}  // namespace ringcnt4_impl_

//! should be simple undirected graph
inline u64 ringcnt4(adjlist<> const& g) {
  u32 n = (u32)g.v_size();
  adjlist<> dg(n), dgv(n);
  for (u32 u = 0; u < n; ++u)
    for (auto [v] : g[u]) (std::make_pair(g[u].size(), u) < std::make_pair(g[v].size(), v) ? dg : dgv).add_arc(u, v);
  return ringcnt4_impl_::run_(dg, dgv);
}
//! vertex ID: 0..n-1
//! should be simple undirected graph
inline u64 ringcnt4(u32 n, vec<ptt<u32>> const& edges) {
  adjlist<> g(n);
  for (auto [u, v] : edges) g.add_edge(u, v);
  return ringcnt4(g);
}

}  // namespace tifa_libs::graph

#endif