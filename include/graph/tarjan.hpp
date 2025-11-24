#ifndef TIFALIBS_GRAPH_TARJAN
#define TIFALIBS_GRAPH_TARJAN

#include "../util/alias_others.hpp"

namespace tifa_libs::graph {

struct tarjan {
  u32 id;
  vecu scc_id, dfn, low;
  vvecu belongs;

  CEXP void build(cT_(vvecu) g) NE {
    u32 cnt = 0, n = u32(g.size());
    vecu s;
    vecb ins(n);
    id = 0, dfn = low = scc_id = vecu(n, n);
    auto dfs = [&](auto&& dfs, u32 u) NE -> void {
      for (dfn[u] = low[u] = cnt++, s.push_back(u), ins[u] = 1; auto v : g[u])
        if (dfn[v] == n) dfs(dfs, v), low[u] = min(low[u], low[v]);
        else if (ins[v]) low[u] = min(low[u], dfn[v]);
      if (low[u] == dfn[u]) {
        belongs.push_back(vecu());
        do {
          const u32 v = s.back();
          s.pop_back();
          ins[v] = 0, belongs[scc_id[v] = id].push_back(v);
          if (v == u) return void(++id);
        } while (1);
      }
    };
    flt_ (u32, i, 0, n)
      if (dfn[i] == n) dfs(dfs, i);
  }
};

}  // namespace tifa_libs::graph

#endif