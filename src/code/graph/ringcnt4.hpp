#ifndef TIFA_LIBS_GRAPH_RINGCNT4
#define TIFA_LIBS_GRAPH_RINGCNT4

#include "adjlist.hpp"

namespace tifa_libs::graph {

//! vertex ID: 0..n-1
//! should be simple undirected graph
template <class F>
inline u64 ringcnt4(u32 n, vec<ptt<u32>> const& edges) {
  vec<u32> deg(n);
  for (auto [u, v] : edges) ++deg[u], ++deg[v];
  adjlist<void> g(n);
  for (auto [u, v] : edges) g.add_edge(u, v);
  adjlist<void> dg(n);
  for (auto [u, v] : edges)
    if (deg[u] > deg[v] || (deg[u] == deg[v] && u > v)) dg.add_arc(u, v);
  u64 ans = 0;
  vec<u32> cnt(n);
  for (u32 u = 0; u < n; ++u) {
    for (auto [v] : dg[u])
      for (auto [w] : g[v]) {
        if (deg[u] < deg[w] || (deg[u] == deg[w] && u <= w)) continue;
        ans += cnt[w]++;
      }
    for (auto [v] : dg[u])
      for (auto [w] : g[v]) cnt[w] = 0;
  }
  return ans;
}

}  // namespace tifa_libs::graph

#endif