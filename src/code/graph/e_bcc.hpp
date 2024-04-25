#ifndef TIFALIBS_GRAPH_E_BCC
#define TIFALIBS_GRAPH_E_BCC

#include "../util/util.hpp"

namespace tifa_libs::graph {

template <class EW>
class e_bcc {
  const vvec<EW> &g;

 public:
  u32 id;
  vecu ebcc_id, dfn, low;
  vecb cut;
  vvecu belongs;

  //! EW need rev_edge
  explicit e_bcc(cT_(vvec<EW>) G) : g(G) { build(); }

  void build() {
    id = 0;
    u32 cnt = 0, n = u32(g.size());
    dfn = low = ebcc_id = vecu(n, n);
    cut = vecb(n, 0);
    std::stack<u32> s;

    auto dfs = [&](auto &&dfs, u32 u, u32 fa, u32 inv_from) -> void {
      dfn[u] = low[u] = cnt++;
      s.push(u);
      for (u32 i = 0; i < g[u].size(); ++i) {
        auto v = g[u][i];
        if (v.to == fa && i == inv_from) continue;
        if (dfn[v.to] == n) {
          dfs(dfs, v.to, u, v.inv);
          low[u] = min(low[u], low[v.to]);
        } else low[u] = min(low[u], dfn[v.to]);
      }
      if (low[u] == dfn[u]) {
        belongs.push_back(vecu());
        do {
          u32 v = s.top();
          s.pop();
          ebcc_id[v] = id;
          belongs[id].push_back(v);
          if (v == u) return void(++id);
        } while (1);
      }
    };

    flt_ (u32, i, 0, n)
      if (dfn[i] == n) dfs(dfs, i, i, -1_u32);
  }
};

}  // namespace tifa_libs::graph

#endif