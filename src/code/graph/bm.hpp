#ifndef TIFALIBS_GRAPH_BM
#define TIFALIBS_GRAPH_BM

#include "../math/isqrt.hpp"
#include "../util/traits.hpp"

namespace tifa_libs::graph {

// cb_relax(now, to)
// @return false if negative cycle detected
template <adjlistw_c G, class F>
requires(!uint_c<TPN G::w_t>) && requires(F relex, u32 now, u32 to) { relex(now, to); }
bool bellman_ford(G CR g, u32 s, F &&cb_relax, vec<TPN G::w_t> &dis) {
  const u32 n = g.size(), sn = math::isqrt(n);
  assert(dis.size() == n);
  vecb vis(n);
  vecu dep(n);
  std::deque<u32> q({s});
  auto upd_q = [&] {
    if (q.size() >= 2 && dis[q.front()] > dis[q.back()]) swap(q.front(), q.back());
  };
  dis[s] = 0, vis[s] = true, dep[s] = 1;
  while (!q.empty()) {
    const u32 u = q.front();
    for (q.pop_front(), upd_q(), vis[u] = false; auto [v, w] : g[u])
      if (dis[u] + w < dis[v]) {
        if (cb_relax(u, v), dis[v] = dis[u] + w; vis[v]) continue;
        if (++dep[v] > n) return false;
        vis[v] = true, ((1 < dep[v] && dep[v] < sn) || dis[v] < TPN G::w_t(q.size() ? dis[q.front()] : 0) ? q.push_front(v) : q.push_back(v)), upd_q();
      }
  }
  return true;
}
// cb_relax(now, to)
template <adjlistw_c G, class F>
std::optional<vec<TPN G::w_t>> bellman_ford(G CR g, u32 s, F &&cb_relax, TPN G::w_t INF = std::numeric_limits<TPN G::w_t>::max() / 2 - 1) {
  vec dis(g.size(), INF);
  return bellman_ford(g, s, std::forward<F>(cb_relax), dis) ? std::optional{dis} : std::nullopt;
}

}  // namespace tifa_libs::graph

#endif