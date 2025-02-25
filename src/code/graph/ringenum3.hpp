#ifndef TIFALIBS_GRAPH_RINGENUM3
#define TIFALIBS_GRAPH_RINGENUM3

#include "../util/traits.hpp"
#include "alist.hpp"

namespace tifa_libs::graph {
namespace ringenum3_impl_ {
template <class F, class G>
requires(alist_c<G> && !alistw_c<G>)
CEXP void run(G CR dg, F&& func) NE {
  const u32 n = dg.size();
  vecb vis(n);
  flt_ (u32, u, 0, n) {
    for (u32 v : dg[u]) vis[v].flip();
    for (u32 v : dg[u])
      for (u32 w : dg[v])
        if (vis[w]) func(u, v, w);
    for (u32 v : dg[u]) vis[v].flip();
  }
}
}  // namespace ringenum3_impl_

//! should be simple undirected graph
// func(u, v, w) forall {u,v,w} is C3
template <class F>
CEXP void ringenum3(spnu deg, vecptu CR edges, F&& func) NE {
  alist dg((u32)deg.size());
  for (auto [u, v] : edges) {
    if (deg[u] < deg[v] || (deg[u] == deg[v] && u > v)) swap(u, v);
    dg.add_arc(u, v);
  }
  ringenum3_impl_::run(dg, std::forward<F>(func));
}
//! vertex ID: 0..n-1
//! should be simple undirected graph
// func(u, v, w) forall {u,v,w} is C3
template <class F>
CEXP void ringenum3(u32 n, vecptu CR edges, F&& func) {
  vecu deg(n);
  for (auto [u, v] : edges) ++deg[u], ++deg[v];
  ringenum3(deg, edges, std::forward<F>(func));
}
CEXP u64 ringcnt3(u32 n, vecptu CR edges) NE {
  u64 ans = 0;
  ringenum3(n, edges, [&](u32, u32, u32) NE { ++ans; });
  return ans;
}

}  // namespace tifa_libs::graph

#endif