#ifndef TIFALIBS_GRAPH_BM
#define TIFALIBS_GRAPH_BM

#include "../util/traits.hpp"
#include "alistw.hpp"

namespace tifa_libs::graph {

// cb_relax(now, to)
template <class T, class F, bool with_deg>
requires(!uint_c<T>) && requires(F relex, u32 now, u32 to) { relex(now, to); }
std::optional<vec<T>> bellman_ford(alistw<T, with_deg> CR fg, u32 s, F &&cb_relax, T INF = std::numeric_limits<T>::max() / 2 - 1) {
  auto &&g = fg.g;
  vec<T> dis(g.size(), INF);
  vecb vis(g.size());
  vecu dep(g.size());
  std::queue<u32> q({s});
  dis[s] = 0, vis[s] = true, dep[s] = 1;
  while (!q.empty()) {
    const u32 u = q.front();
    q.pop(), vis[u] = false;
    for (auto [v, w] : g[u])
      if (dis[u] + w < dis[v]) {
        cb_relax(u, v), dis[v] = dis[u] + w;
        if (vis[v]) continue;
        if (++dep[v] > g.size()) return {};
        vis[v] = true, q.push(v);
      }
  }
  return dis;
}

}  // namespace tifa_libs::graph

#endif