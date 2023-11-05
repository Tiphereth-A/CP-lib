#ifndef TIFA_LIBS_GRAPH_KOSARAJU
#define TIFA_LIBS_GRAPH_KOSARAJU

#include "alist.hpp"
#include "alistr.hpp"

namespace tifa_libs::graph {

class kosaraju {
  const alist::value_type &g, &rev_g;

 public:
  alist dag;
  vec<u32> scc_id;
  vvec<u32> belongs;

  explicit kosaraju(alist const &g) : kosaraju(g, alistr(g)) {}
  kosaraju(alist const &g, alist const &rev_g) : g(g.g), rev_g(rev_g.g) { build(); }

 private:
  void build() {
    vec<bool> vis(g.size());
    vec<u32> ord;
    auto dfs = [&, this](auto &&dfs, u32 idx) {
      if (vis[idx]) return;
      vis[idx] = true;
      for (auto to : g[idx]) dfs(dfs, to);
      ord.push_back(idx);
    };
    auto rdfs = [this](auto &&rdfs, u32 idx, u32 cnt) {
      if (~scc_id[idx]) return;
      scc_id[idx] = cnt;
      for (auto to : rev_g[idx]) rdfs(rdfs, to, cnt);
    };
    for (u32 i = 0; i < g.size(); ++i) dfs(dfs, i);
    std::reverse(ord.begin(), ord.end());
    scc_id.resize(g.size(), -1_u32);
    u32 cnt = 0;
    for (u32 i : ord)
      if (!~scc_id[i]) rdfs(rdfs, i, cnt++);
    dag.g.resize(cnt);
    belongs.resize(cnt);
    for (u32 i = 0; i < g.size(); ++i) {
      belongs[scc_id[i]].push_back(i);
      for (auto to : g[i])
        if (u32 x = scc_id[i], y = scc_id[to]; x != y) dag.add_arc(x, y);
    }
  }
};

}  // namespace tifa_libs::graph

#endif