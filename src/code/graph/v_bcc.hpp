#ifndef TIFALIBS_GRAPH_V_BCC
#define TIFALIBS_GRAPH_V_BCC

#include "../util/util.hpp"

namespace tifa_libs::graph {

template <class EW>
class v_bcc {
  const vvec<EW> &g;

 public:
  u32 id;
  vec<u32> dfn, low;
  vec<bool> cut;
  vvec<u32> belongs;

  //! EW need rev_edge
  explicit constexpr v_bcc(vvec<EW> const &G) : g(G) { build(); }

  constexpr void build() {
    id = 0;
    u32 cnt = 0, n = u32(g.size());
    dfn = low = vec<u32>(n, n);
    cut = vec<bool>(n, 0);
    std::stack<u32> s;

    auto dfs = [&](auto &&dfs, u32 u, u32 fa, u32 inv_from) -> void {
      dfn[u] = low[u] = cnt++;
      if (u == fa && g[u].size() == 0) cut[u] = 1, belongs.push_back(vec<u32>(1, u)), ++id;
      s.push(u);
      for (u32 i = 0; i < g[u].size(); ++i) {
        auto v = g[u][i];
        if (v.to == fa && i == inv_from) continue;
        if (dfn[v.to] == n) {
          dfs(dfs, v.to, u, v.inv);
          low[u] = std::min(low[u], low[v.to]);
          if (low[v.to] >= dfn[u]) {
            u32 p;
            cut[u] = 1, belongs.push_back(vec<u32>(1, u));
            do {
              p = s.top(), s.pop();
              belongs[id].push_back(p);
            } while (p != v.to);
            id++;
          }
        } else low[u] = std::min(low[u], dfn[v.to]);
      }
    };

    for (u32 i = 0; i < n; ++i)
      if (dfn[i] == n) dfs(dfs, i, i, -1_u32);
  }
};

}  // namespace tifa_libs::graph

#endif