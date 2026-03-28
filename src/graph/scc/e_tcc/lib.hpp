#pragma once

#include "../../../ds/dsu/basic/lib.hpp"
#include "../../../ds/dsu/delineation/lib.hpp"
#include "../../ds/alist/lib.hpp"

namespace tifa_libs {

struct e_tcc {
  vecu dfn, low, post, path, deg;
  dsu_basic<> dsu;
  vvecu belongs;

  //! g should be undirected
  template <class Et, class... Info>
  CEXP e_tcc(alist<Et, Info...> CR g) NE : dfn(g.vsize(), -1_u32), low(g.vsize()), post(g.vsize()), path(g.vsize(), -1_u32), deg(g.vsize()), dsu(g.vsize()) {
    const u32 n = g.vsize();
    u32 tot = -1_u32;
    const auto dfs = [&](auto&& f, u32 u, u32 t = -1_u32) -> void {
      u32 pc{};
      for (dfn[u] = low[u] = ++tot; u32 v : g[u]) {
        if (v == u || (v == t && !pc++)) continue;
        if (~dfn[v]) {
          if (dfn[v] < dfn[u]) {
            ++deg[u], low[u] = std::min(low[u], dfn[v]);
            continue;
          }
          --deg[u];
          for (auto& p = path[u]; ~p && dfn[p] <= dfn[v] && dfn[v] <= post[p]; p = path[p])
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
    belongs = dsu_delineation(dsu);
  }
};

}  // namespace tifa_libs
