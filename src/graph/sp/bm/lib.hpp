#pragma once

#include "../../../math/iroot/sqrt/lib.hpp"
#include "../../../util/alias/others/lib.hpp"
#include "../../../util/traits/math/lib.hpp"
#include "../../ds/graph_c/lib.hpp"

namespace tifa_libs {

// cb_relax(now, to)
// @return false if negative cycle detected
template <wgraph_c G, class F>
requires(!uint_c<TPN G::Et>) && requires(F relex, u32 now, u32 to) { relex(now, to); }
bool bellman_ford(G CR g, u32 s, F&& cb_relax, vec<TPN G::Et>& dis) NE {
  const u32 n = g.vsize(), sn = isqrt(n);
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
        vis[v] = true;
        (1 < dep[v] && dep[v] < sn) || dis[v] < TPN G::Et(q.size() ? dis[q.front()] : 0) ? q.push_front(v) : q.push_back(v);
        upd_q();
      }
  }
  return true;
}
// cb_relax(now, to)
template <wgraph_c G, class F>
auto bellman_ford(G CR g, u32 s, F&& cb_relax, TPN G::Et INF = std::numeric_limits<TPN G::Et>::max() / 2 - 1) NE {
  std::optional ret{vec<TPN G::Et>(g.vsize(), INF)};
  if (!bellman_ford(g, s, std::forward<F>(cb_relax), ret.value())) ret = std::nullopt;
  return ret;
}

}  // namespace tifa_libs
