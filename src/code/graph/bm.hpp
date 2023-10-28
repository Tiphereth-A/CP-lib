#ifndef TIFA_LIBS_GRAPH_BM
#define TIFA_LIBS_GRAPH_BM

#include "../util/traits.hpp"
#include "adjlist.hpp"

namespace tifa_libs::graph {

// cb_relax(now, to)
template <class W, class F>
std::optional<vec<W>> bellman_ford(adjlist<W> const &g, u32 s, F cb_relax, W INF = std::numeric_limits<W>::max() / 2 - 1) {
  static_assert(!is_uint<W>::value);
  vec<W> dis(g.v_size(), INF);
  vec<bool> vis(g.v_size());
  vec<u32> dep(g.v_size());
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
        if (++dep[to] > g.v_size()) return {};
        vis[to] = true;
        q.push(to);
      }
  }
  return dis;
}

}  // namespace tifa_libs::graph

#endif