#ifndef TIFALIBS_GRAPH_TARJAN
#define TIFALIBS_GRAPH_TARJAN

#include "../util/util.hpp"

namespace tifa_libs::graph {

struct tarjan {
  u32 id;
  vecu scc_id, dfn, low;
  vvecu belongs;

  constexpr void build(vvecu const &g) {
    id = 0;
    u32 cnt = 0, n = u32(g.size());
    vecu s;
    vecb ins(n);
    dfn = low = scc_id = vecu(n, n);
    auto dfs = [&](auto &&dfs, u32 u) -> void {
      dfn[u] = low[u] = cnt++, s.push_back(u), ins[u] = 1;
      for (auto v : g[u])
        if (dfn[v] == n) {
          dfs(dfs, v);
          low[u] = std::min(low[u], low[v]);
        } else if (ins[v]) low[u] = std::min(low[u], dfn[v]);
      if (low[u] == dfn[u]) {
        belongs.push_back(vecu());
        do {
          u32 v = s.back();
          s.pop_back(), ins[v] = 0;
          scc_id[v] = id;
          belongs[id].push_back(v);
          if (v == u) return void(++id);
        } while (1);
      }
    };
    for (u32 i = 0; i < n; ++i)
      if (dfn[i] == n) dfs(dfs, i);
  }
};

}  // namespace tifa_libs::graph

#endif