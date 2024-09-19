#ifndef TIFALIBS_GRAPH_BM
#define TIFALIBS_GRAPH_BM

#include "../util/traits.hpp"

namespace tifa_libs::graph {

// cb_relax(now, to)
template <adjlistw_c G, class F, class T = TPN G::w_t>
requires(!uint_c<T>) && requires(F relex, u32 now, u32 to) { relex(now, to); }
std::optional<vec<T>> bellman_ford(G CR g, u32 s, F &&cb_relax, T INF = std::numeric_limits<T>::max() / 2 - 1) {
  vec<T> dis(g.size(), INF);
  vecb vis(g.size());
  vecu dep(g.size());
  std::queue<u32> q({s});
  dis[s] = 0, vis[s] = true, dep[s] = 1;
  while (!q.empty()) {
    const u32 u = q.front();
    for (q.pop(), vis[u] = false; auto [v, w] : g[u])
      if (dis[u] + w < dis[v]) {
        if (cb_relax(u, v), dis[v] = dis[u] + w; vis[v]) continue;
        if (++dep[v] > g.size()) return {};
        vis[v] = true, q.push(v);
      }
  }
  return dis;
}

}  // namespace tifa_libs::graph

#endif