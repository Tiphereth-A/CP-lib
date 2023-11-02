#ifndef TIFA_LIBS_GRAPH_DIJKSTRA
#define TIFA_LIBS_GRAPH_DIJKSTRA

#include "../util/traits.hpp"
#include "adjlist.hpp"

namespace tifa_libs::graph {

// cb_relax(now, to)
template <class VW, class EW, class F>
vec<EW> dijkstra(adjlist<VW, EW> const &g, u32 s, F cb_relax, EW INF = std::numeric_limits<EW>::max() / 2 - 1) {
  static_assert(!is_sint<EW>::value);
  vec<EW> dis(g.v_size(), INF);
  vec<bool> vis(g.v_size());
  pqg<std::pair<EW, u32>> q;
  q.emplace(dis[s] = 0, s);
  while (!q.empty()) {
    auto [dis_now, now] = q.top();
    q.pop();
    if (vis[now]) continue;
    vis[now] = true;
    for (auto [to, w] : g[now])
      if (dis[now] + w < dis[to]) {
        cb_relax(now, to);
        dis[to] = dis[now] + w;
        if (!vis[to]) q.emplace(dis[to], to);
      }
  }
  return dis;
}

}  // namespace tifa_libs::graph

#endif