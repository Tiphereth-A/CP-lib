#pragma once

#include "../../../ds/heap/radix/lib.hpp"
#include "../../../util/traits/math/lib.hpp"
#include "../../ds/graph_c/lib.hpp"

namespace tifa_libs {

// relax(now, to)
template <wgraph_c G, class F, class T = TPN G::Et>
requires(!sint_c<T>) && requires(F relex, u32 now, u32 to) { relex(now, to); }
CEXP vec<T> dijkstra(G CR g, u32 s, F&& relax, T INF = inf_v<T>) NE {
  vec<T> dis(g.vsize(), INF);
  vecb vis(g.vsize());
  rheap<T, u32> q;
  q.emplace(dis[s] = 0, s);
  while (!q.empty()) {
    auto [dis_now, u] = q.top();
    if (dis_now > INF) dis_now = INF;
    if (q.pop(); vis[u]) continue;
    for (vis[u] = true; auto [v, w] : g[u])
      if (dis[u] + w < dis[v])
        if (relax(u, v), dis[v] = dis[u] + w; !vis[v]) q.emplace(dis[v], v);
  }
  return dis;
}

}  // namespace tifa_libs
