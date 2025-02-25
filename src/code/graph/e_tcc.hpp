#ifndef TIFALIBS_GRAPH_E_TCC
#define TIFALIBS_GRAPH_E_TCC

#include "../ds/dsu_basic.hpp"
#include "../ds/dsu_delineation.hpp"
#include "alist.hpp"

namespace tifa_libs::graph {

struct e_tcc {
  vecu dfn, low, post, path, deg;
  ds::dsu_basic<> dsu;
  vvecu belongs;

  //! g should be undirected
  template <bool with_deg>
  e_tcc(alist<with_deg> CR g) NE : dfn(g.size(), -1_u32), low(g.size()), post(g.size()), path(g.size(), -1_u32), deg(g.size()), dsu(g.size()) {
    const u32 n = g.size();
    u32 tot = -1_u32;
    const auto dfs = [&](auto &&f, u32 u, u32 t = -1_u32) -> void {
      u32 pc{};
      for (dfn[u] = low[u] = ++tot; u32 v : g[u]) {
        if (v == u || (v == t && !pc++)) continue;
        if (~dfn[v]) {
          if (dfn[v] < dfn[u]) {
            ++deg[u], low[u] = std::min(low[u], dfn[v]);
            continue;
          }
          --deg[u];
          for (auto &p = path[u]; ~p && dfn[p] <= dfn[v] && dfn[v] <= post[p]; p = path[p])
            dsu.merge(u, p), deg[u] += deg[p];
          continue;
        }
        if (f(f, v, u); !~path[v] && deg[v] <= 1) {
          low[u] = min(low[u], low[v]), deg[u] += deg[v];
          continue;
        }
        if (!deg[v]) v = path[v];
        if (low[u] > low[v]) low[u] = min(low[u], low[v]), swap(v, path[u]);
        for (; ~v; v = path[v]) dsu.merge(u, v), deg[u] += deg[v];
      }
      post[u] = tot;
    };
    flt_ (u32, u, 0, n)
      if (!~dfn[u]) dfs(dfs, u);
    belongs = ds::dsu_delineation(dsu);
  }
};

}  // namespace tifa_libs::graph

#endif