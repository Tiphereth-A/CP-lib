#pragma once

#include "../../util/alias/others/lib.hpp"
#include "../ds/graph_c/lib.hpp"

namespace tifa_libs {

template <bool directed, graph_c G>
CEXP vecptu find_cycle(G CR g) NE {
  flt_ (u32, i, 0, g.vsize())
    for (auto j : g[i])
      if (i == (u32)j) return vecptu{{i, i}};
  vecu pidx(g.vsize(), -1_u32), vis(g.vsize(), 0);
  vecptu cycle;
  bool fin = false;
  auto f = [&](auto&& f, u32 now, u32 pval, u32 fa) NE -> u32 {
    for (pidx[now] = pval, vis[now] = 1; u32 to : g[now]) {
      if (fin) return -1_u32;
      if CEXP (!directed)
        if (to == fa) continue;
      if (pidx[to] == pidx[now]) {
        cycle.emplace_back(now, to);
        return to;
      }
      if (vis[to]) continue;
      if (u32 nxt = f(f, to, pval, now); ~nxt) {
        if (cycle.emplace_back(now, to); now == nxt) {
          fin = true;
          return -1_u32;
        }
        return nxt;
      }
    }
    return pidx[now] = -1_u32;
  };
  flt_ (u32, i, 0, g.vsize()) {
    if (vis[i]) continue;
    if (f(f, i, i, -1_u32); fin) {
      reverse(cycle);
      return cycle;
    }
  }
  return vecptu{};
}

}  // namespace tifa_libs
