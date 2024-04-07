#ifndef TIFALIBS_GRAPH_RINGENUM3
#define TIFALIBS_GRAPH_RINGENUM3

#include "alist.hpp"

namespace tifa_libs::graph {
namespace ringenum3_impl_ {
template <class F, bool with_deg>
constexpr void run(alist<with_deg> const& dg, F&& func) {
  u32 n = (u32)dg.g.size();
  vecb vis(n);
  for (u32 u = 0; u < n; ++u) {
    for (u32 v : dg.g[u]) vis[v].flip();
    for (u32 v : dg.g[u])
      for (u32 w : dg.g[v])
        if (vis[w]) func(u, v, w);
    for (u32 v : dg.g[u]) vis[v].flip();
  }
}
}  // namespace ringenum3_impl_

//! should be simple undirected graph
// func(u, v, w) forall {u,v,w} is C3
template <class F>
constexpr void ringenum3(vecu const& deg, vecpt<u32> const& edges, F&& func) {
  alist<false> dg((u32)deg.size());
  for (auto [u, v] : edges) {
    if (deg[u] < deg[v] || (deg[u] == deg[v] && u > v)) std::swap(u, v);
    dg.add_arc(u, v);
  }
  ringenum3_impl_::run(dg, std::forward<F>(func));
}
//! vertex ID: 0..n-1
//! should be simple undirected graph
// func(u, v, w) forall {u,v,w} is C3
template <class F>
constexpr void ringenum3(u32 n, vecpt<u32> const& edges, F&& func) {
  vecu deg(n);
  for (auto [u, v] : edges) ++deg[u], ++deg[v];
  ringenum3(deg, edges, std::forward<F>(func));
}
constexpr u64 ringcnt3(u32 n, vecpt<u32> const& edges) {
  u64 ans = 0;
  ringenum3(n, edges, [&](u32, u32, u32) { ++ans; });
  return ans;
}

}  // namespace tifa_libs::graph

#endif