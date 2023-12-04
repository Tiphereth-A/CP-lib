#ifndef TIFALIBS_GRAPH_TARJAN
#define TIFALIBS_GRAPH_TARJAN

#include "../util/util.hpp"

namespace tifa_libs::graph {

template <class EW>
class tarjan {
  const vvec<EW> &g;

 public:
  u32 id;
  vec<u32> scc_id, dfn, low;
  vvec<u32> belongs;
  tarjan(vvec<EW> const &G) : g(G) { get_scc(); }
  void get_scc() {
    id = 0;
    u32 cnt = 0, n = u32(g.size());
    std::stack<u32> s;
    vec<bool> ins(n);
    dfn = low = scc_id = vec<u32>(n, n);
    auto dfs = [&](auto &&dfs, u32 u) -> void {
      dfn[u] = low[u] = cnt++, s.push(u), ins[u] = 1;
      for (auto v : g[u])
        if (dfn[v] == n) {
          dfs(dfs, v);
          low[u] = std::min(low[u], low[v]);
        } else if (ins[v]) low[u] = std::min(low[u], dfn[v]);
      if (low[u] == dfn[u]) {
        belongs.push_back(vec<u32>());
        do {
          u32 v = s.top();
          s.pop(), ins[v] = 0;
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