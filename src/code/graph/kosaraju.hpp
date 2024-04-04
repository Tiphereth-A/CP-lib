#ifndef TIFALIBS_GRAPH_KOSARAJU
#define TIFALIBS_GRAPH_KOSARAJU

#include "alist.hpp"
#include "alistr.hpp"

namespace tifa_libs::graph {

template <bool with_deg = false>
class kosaraju {
  const alist<with_deg>::value_type &g, &rev_g;

 public:
  alist<with_deg> dag;
  vecu scc_id;
  vvecu belongs;

  explicit constexpr kosaraju(alist<with_deg> const &g) : kosaraju(g, alistr(g)) {}
  constexpr kosaraju(alist<with_deg> const &g, alist<with_deg> const &rev_g) : g(g.g), rev_g(rev_g.g) { build(); }

 private:
  constexpr void build() {
    vecb vis(g.size());
    vecu ord;
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