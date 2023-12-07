#ifndef TIFALIBS_GRAPH_DIJKSTRA
#define TIFALIBS_GRAPH_DIJKSTRA

#include "../util/traits.hpp"
#include "alistw.hpp"

namespace tifa_libs::graph {

// relax(now, to)
template <class T, class F>
vec<T> dijkstra(alistw<T> const &fg, u32 s, F relax, T INF = std::numeric_limits<T>::max() / 2 - 1) {
  static_assert(!is_sint<T>::value);
  auto &&g = fg.g;
  vec<T> dis(g.size(), INF);
  vec<bool> vis(g.size());
  pqg<std::pair<T, u32>> q;
  q.emplace(dis[s] = 0, s);
  while (!q.empty()) {
    auto [dis_now, now] = q.top();
    q.pop();
    if (vis[now]) continue;
    vis[now] = true;
    for (auto [to, w] : g[now])
      if (dis[now] + w < dis[to]) {
        relax(now, to);
        dis[to] = dis[now] + w;
        if (!vis[to]) q.emplace(dis[to], to);
      }
  }
  return dis;
}

}  // namespace tifa_libs::graph

#endif