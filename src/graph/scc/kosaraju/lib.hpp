#pragma once

#include "../../ds/alist/lib.hpp"
#include "../../make_graphr/lib.hpp"

namespace tifa_libs {

template <graph_c G>
class kosaraju {
  G CR g;
  G CR rev_g;

 public:
  G dag;
  vecu scc_id;
  vvecu belongs;

  CEXP kosaraju(G CR g, G CR rev_g) NE : g(g), rev_g(rev_g), dag(0) { build(); }
  CEXP kosaraju(G CR g) NE : kosaraju(g, make_graphr(g)) {}

 private:
  CEXP void build() NE {
    vecb vis(g.vsize());
    vecu ord;
    auto dfs = [&, this](auto&& dfs, u32 idx) NE {
      if (vis[idx]) return;
      for (vis[idx] = 1; auto to : g[idx]) dfs(dfs, to);
      ord.push_back(idx);
    };
    auto rdfs = [this](auto&& rdfs, u32 idx, u32 cnt) NE {
      if (~scc_id[idx]) return;
      for (scc_id[idx] = cnt; auto to : rev_g[idx]) rdfs(rdfs, to, cnt);
    };
    flt_ (u32, i, 0, g.vsize()) dfs(dfs, i);
    reverse(ord), scc_id.resize(g.vsize(), -1_u32);
    u32 cnt = 0;
    for (u32 i : ord)
      if (!~scc_id[i]) rdfs(rdfs, i, cnt++);
    dag = G(cnt), belongs.resize(cnt);
    flt_ (u32, i, 0, g.vsize())
      for (belongs[scc_id[i]].push_back(i); auto to : g[i])
        if (u32 x = scc_id[i], y = scc_id[to]; x != y) dag.add_arc(x, y);
  }
};

}  // namespace tifa_libs
