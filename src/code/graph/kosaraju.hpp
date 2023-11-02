#ifndef TIFA_LIBS_GRAPH_KOSARAJU
#define TIFA_LIBS_GRAPH_KOSARAJU

#include "adjlist.hpp"

namespace tifa_libs::graph {

class kosaraju {
  const adjlist<> &g, &rev_g;

 public:
  adjlist<> dag;
  vec<u32> scc_id;
  vvec<u32> belongs;

  kosaraju(adjlist<> const &g, adjlist<> const &rev_g) : g(g), rev_g(rev_g) { build(); }

 private:
  void build() {
    vec<bool> vis(g.v_size());
    vec<u32> ord;
    auto dfs = [&, this](auto &&dfs, u32 idx) {
      if (vis[idx]) return;
      vis[idx] = true;
      for (auto [to] : g[idx]) dfs(dfs, to);
      ord.push_back(idx);
    };
    auto rdfs = [this](auto &&rdfs, u32 idx, u32 cnt) {
      if (~scc_id[idx]) return;
      scc_id[idx] = cnt;
      for (auto [to] : rev_g[idx]) rdfs(rdfs, to, cnt);
    };
    for (u32 i = 0; i < g.v_size(); ++i) dfs(dfs, i);
    std::reverse(ord.begin(), ord.end());
    scc_id.resize(g.v_size(), -1_u32);
    u32 cnt = 0;
    for (u32 i : ord)
      if (!~scc_id[i]) rdfs(rdfs, i, cnt++);
    dag.reset_v_size(cnt);
    belongs.resize(cnt);
    for (u32 i = 0; i < g.v_size(); ++i) {
      belongs[scc_id[i]].push_back(i);
      for (auto [to] : g[i])
        if (u32 x = scc_id[i], y = scc_id[to]; x != y) dag.add_arc(x, y);
    }
  }
};

}  // namespace tifa_libs::graph

#endif