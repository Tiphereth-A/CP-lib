#ifndef TIFALIBS_GRAPH_FIND_CYCLE
#define TIFALIBS_GRAPH_FIND_CYCLE

#include "alist.hpp"

namespace tifa_libs::graph {

template <bool directed, bool with_deg>
CEXP vecptu find_cycle(alist<with_deg> CR fg) {
  auto&& g = fg.g;
  flt_ (u32, i, 0, (u32)g.size())
    for (u32 j : g[i])
      if (i == j) return vecptu{{i, i}};
  vecu pidx(g.size(), -1_u32), vis(g.size(), 0);
  vecptu cycle;
  bool fin = false;
  auto f = [&](auto&& f, u32 now, u32 pval, u32 fa) -> u32 {
    for (pidx[now] = pval, vis[now] = 1; u32 to : g[now]) {
      if (fin) return -1_u32;
      if CEXP (!directed)
        if (to == fa) continue;
      if (pidx[to] == pidx[now]) return cycle.emplace_back(now, to), to;
      if (vis[to]) continue;
      if (u32 nxt = f(f, to, pval, now); ~nxt) {
        if (cycle.emplace_back(now, to); now == nxt) return (fin = true), -1_u32;
        return nxt;
      }
    }
    return pidx[now] = -1_u32;
  };
  flt_ (u32, i, 0, (u32)g.size()) {
    if (vis[i]) continue;
    if (f(f, i, i, -1_u32); fin) return std::ranges::reverse(cycle), cycle;
  }
  return vecptu{};
}

}  // namespace tifa_libs::graph

#endif