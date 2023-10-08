#ifndef TIFA_LIBS_GRAPH_DIJKSTRA
#define TIFA_LIBS_GRAPH_DIJKSTRA

#include "../util/util.hpp"

namespace tifa_libs::ds {

template <class W, auto INF = std::numeric_limits<W>::max() / 2 - 1>
vec<W> dijkstra(vvp<size_t, W> const &g, size_t s) {
  vec<W> dis(g.size(), INF);
  pqg<std::pair<W, size_t>> q;
  q.emplace(dis[s] = 0, s);
  while (!q.empty()) {
    auto [dis_now, now] = q.top();
    q.pop();
    if (dis[now] < dis_now) continue;
    for (auto [to, w] : g[now])
      if (dis[to] > dis[now] + w) q.emplace(dis[to] = dis[now] + w, to);
  }
  return dis;
}

}  // namespace tifa_libs::ds

#endif