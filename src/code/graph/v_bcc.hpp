#ifndef TIFALIBS_GRAPH_V_BCC
#define TIFALIBS_GRAPH_V_BCC

#include "../util/util.hpp"

namespace tifa_libs::graph {

template <class EW>
class v_bcc {
  vvec<EW> CR g;

 public:
  u32 id;
  vecu dfn, low;
  vecb cut;
  vvecu belongs;

  //! EW need rev_edge
  explicit v_bcc(cT_(vvec<EW>) G) : g(G) { build(); }

  void build() {
    u32 cnt = 0, n = u32(g.size());
    id = 0, dfn = low = vecu(n, n), cut = vecb(n, 0);
    std::stack<u32> s;
    auto dfs = [&](auto &&dfs, u32 u, u32 fa, u32 inv_from) -> void {
      if (dfn[u] = low[u] = cnt++; u == fa && g[u].size() == 0) cut[u] = 1, belongs.push_back(vecu(1, u)), ++id;
      s.push(u);
      flt_ (u32, i, 0, (u32)g[u].size()) {
        auto v = g[u][i];
        if (v.to == fa && i == inv_from) continue;
        if (dfn[v.to] == n) {
          if (dfs(dfs, v.to, u, v.inv), low[u] = min(low[u], low[v.to]); low[v.to] >= dfn[u]) {
            u32 p;
            cut[u] = 1, belongs.push_back(vecu(1, u));
            do p = s.top(), s.pop(), belongs[id].push_back(p);
            while (p != v.to);
            ++id;
          }
        } else low[u] = min(low[u], dfn[v.to]);
      }
    };
    flt_ (u32, i, 0, n)
      if (dfn[i] == n) dfs(dfs, i, i, -1_u32);
  }
};

}  // namespace tifa_libs::graph

#endif