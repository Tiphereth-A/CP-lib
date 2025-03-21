#ifndef TIFALIBS_GRAPH_KOSARAJU
#define TIFALIBS_GRAPH_KOSARAJU

#include "alist.hpp"
#include "make_alistr.hpp"

namespace tifa_libs::graph {

template <bool with_deg = false>
class kosaraju {
  alist<with_deg> CR g, &rev_g;

 public:
  alist<with_deg> dag;
  vecu scc_id;
  vvecu belongs;

  CEXPE kosaraju(alist<with_deg> CR g) NE : kosaraju(g, make_alistr(g)) {}
  CEXP kosaraju(alist<with_deg> CR g, alist<with_deg> CR rev_g) NE : g(g), rev_g(rev_g) { build(); }

 private:
  CEXP void build() NE {
    vecb vis(g.size());
    vecu ord;
    auto dfs = [&, this](auto &&dfs, u32 idx) NE {
      if (vis[idx]) return;
      for (vis[idx] = 1; auto to : g[idx]) dfs(dfs, to);
      ord.push_back(idx);
    };
    auto rdfs = [this](auto &&rdfs, u32 idx, u32 cnt) NE {
      if (~scc_id[idx]) return;
      for (scc_id[idx] = cnt; auto to : rev_g[idx]) rdfs(rdfs, to, cnt);
    };
    flt_ (u32, i, 0, (u32)g.size()) dfs(dfs, i);
    reverse(ord), scc_id.resize(g.size(), -1_u32);
    u32 cnt = 0;
    for (u32 i : ord)
      if (!~scc_id[i]) rdfs(rdfs, i, cnt++);
    dag.g.resize(cnt), belongs.resize(cnt);
    flt_ (u32, i, 0, (u32)g.size())
      for (belongs[scc_id[i]].push_back(i); auto to : g[i])
        if (u32 x = scc_id[i], y = scc_id[to]; x != y) dag.add_arc(x, y);
  }
};

}  // namespace tifa_libs::graph

#endif