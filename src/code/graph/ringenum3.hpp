#ifndef TIFA_LIBS_GRAPH_RINGENUM3
#define TIFA_LIBS_GRAPH_RINGENUM3

#include "adjlist.hpp"

namespace tifa_libs::graph {

//! vertex ID: 0..n-1
//! should be simple undirected graph
// func(u, v, w) forall {u,v,w} is C3
template <class F>
inline void ringenum3(u32 n, vec<ptt<u32>> const& edges, F func) {
  vec<u32> deg(n);
  for (auto [u, v] : edges) ++deg[u], ++deg[v];
  adjlist<void> dg(n);
  for (auto [u, v] : edges) {
    if (deg[u] < deg[v] || (deg[u] == deg[v] && u > v)) std::swap(u, v);
    dg.add_arc(u, v);
  }
  vec<bool> vis(n);
  for (u32 u = 0; u < n; ++u) {
    for (auto [v] : dg[u]) vis[v].flip();
    for (auto [v] : dg[u])
      for (auto [w] : dg[v])
        if (vis[w]) func(u, v, w);
    for (auto [v] : dg[u]) vis[v].flip();
  }
}

}  // namespace tifa_libs::graph

#endif