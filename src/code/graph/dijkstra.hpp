#ifndef TIFALIBS_GRAPH_DIJKSTRA
#define TIFALIBS_GRAPH_DIJKSTRA

#include "../ds/radix_heap.hpp"
#include "../util/traits.hpp"
#include "alistw.hpp"

namespace tifa_libs::graph {

// relax(now, to)
template <class T, class F, bool with_deg>
requires(!sint_c<T>) && requires(F relex, u32 now, u32 to) { relex(now, to); }
CEXP vec<T> dijkstra(alistw<T, with_deg> CR fg, u32 s, F &&relax, T INF = std::numeric_limits<T>::max() / 2 - 1) {
  auto &&g = fg.g;
  vec<T> dis(g.size(), INF);
  vecb vis(g.size());
  ds::rheap<T, u32> q;
  q.emplace(dis[s] = 0, s);
  while (!q.empty()) {
    auto [dis_now, u] = q.top();
    if (dis_now > INF) dis_now = INF;
    q.pop();
    if (vis[u]) continue;
    vis[u] = true;
    for (auto [v, w] : g[u])
      if (dis[u] + w < dis[v]) {
        relax(u, v);
        dis[v] = dis[u] + w;
        if (!vis[v]) q.emplace(dis[v], v);
      }
  }
  return dis;
}

}  // namespace tifa_libs::graph

#endif