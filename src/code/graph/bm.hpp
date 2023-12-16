#ifndef TIFALIBS_GRAPH_BM
#define TIFALIBS_GRAPH_BM

#include "../util/traits.hpp"
#include "alistw.hpp"

namespace tifa_libs::graph {

// cb_relax(now, to)
template <class T, class F>
  requires(!uint_c<T>)
std::optional<vec<T>> bellman_ford(alistw<T> const &fg, u32 s, F cb_relax, T INF = std::numeric_limits<T>::max() / 2 - 1) {
  auto &&g = fg.g;
  vec<T> dis(g.size(), INF);
  vec<bool> vis(g.size());
  vec<u32> dep(g.size());
  std::queue<u32> q;
  q.push(s);
  dis[s] = 0;
  vis[s] = true;
  dep[s] = 1;
  while (!q.empty()) {
    u32 now = q.front();
    q.pop();
    vis[now] = false;
    for (auto [to, w] : g[now])
      if (dis[now] + w < dis[to]) {
        cb_relax(now, to);
        dis[to] = dis[now] + w;
        if (vis[to]) continue;
        if (++dep[to] > g.size()) return {};
        vis[to] = true;
        q.push(to);
      }
  }
  return dis;
}

}  // namespace tifa_libs::graph

#endif