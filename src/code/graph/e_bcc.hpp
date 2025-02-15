#ifndef TIFALIBS_GRAPH_E_BCC
#define TIFALIBS_GRAPH_E_BCC

#include "../util/util.hpp"

namespace tifa_libs::graph {

template <class EW>
class e_bcc {
  vvec<EW> CR g;

 public:
  u32 id;
  vecu ebcc_id, dfn, low;
  vecb cut;
  vvecu belongs;

  //! EW need rev_edge
  CEXPE e_bcc(vvec<EW> CR G) NE : g(G) { build(); }

  CEXP void build() NE {
    u32 cnt = 0, n = u32(g.size());
    id = 0, dfn = low = ebcc_id = vecu(n, n), cut = vecb(n, 0);
    vecu s;
    auto f = [&](auto &&f, u32 u, u32 fa, u32 inv_from) NE -> void {
      dfn[u] = low[u] = cnt++, s.push_back(u);
      flt_ (u32, i, 0, (u32)g[u].size()) {
        auto v = g[u][i];
        if (v.to == fa && i == inv_from) continue;
        if (dfn[v.to] == n) f(f, v.to, u, v.inv), low[u] = min(low[u], low[v.to]);
        else low[u] = min(low[u], dfn[v.to]);
      }
      if (low[u] == dfn[u]) {
        belongs.push_back(vecu());
        do {
          const u32 v = s.back();
          if (s.pop_back(), ebcc_id[v] = id, belongs[id].push_back(v); v == u) return void(++id);
        } while (1);
      }
    };
    flt_ (u32, i, 0, n)
      if (dfn[i] == n) f(f, i, i, -1_u32);
  }
};

}  // namespace tifa_libs::graph

#endif