#ifndef TIFALIBS_GRAPH_E_BCC
#define TIFALIBS_GRAPH_E_BCC

#include "eog.hpp"

namespace tifa_libs::graph {

struct e_bcc {
  vecu dfn, low;
  vvecu belongs;

  //! g should be undirect
  template <bool with_deg>
  CEXP e_bcc(eog<with_deg> CR g) NE : dfn(g.size()), low(g.size()) {
    vecu stk;
    u32 tot = 0;
    auto tarjan = [&](auto&& f, u32 u, u32 fa_eid) -> void {
      dfn[u] = low[u] = ++tot;
      stk.push_back(u);
      g.foreach(u, [&](u32 eid, u32 v, u32) {
        if (!dfn[v]) f(f, v, eid), low[u] = min(low[u], low[v]);
        else if (eid != fa_eid && eid != (fa_eid ^ 1)) low[u] = min(low[u], dfn[v]);
      });
      if (low[u] == dfn[u]) {
        vecu res;
        u32 p;
        do res.push_back(p = stk.back()), stk.pop_back();
        while (u != p);
        belongs.emplace_back(std::move(res));
      }
    };
    flt_ (u32, i, 0, g.size())
      if (!dfn[i]) tarjan(tarjan, i, -1_u32);
  }
};

}  // namespace tifa_libs::graph

#endif