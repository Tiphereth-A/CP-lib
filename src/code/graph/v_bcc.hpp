#ifndef TIFALIBS_GRAPH_V_BCC
#define TIFALIBS_GRAPH_V_BCC

#include "alist.hpp"

namespace tifa_libs::graph {

template <bool get_vcut = false, bool get_ecut = false, bool get_belongs = true>
struct v_bcc {
  static_assert(!get_ecut || (!get_vcut && !get_belongs));
  vecu dfn, low;
  vvecu belongs;
  vecb vcut;
  vecptu ecut;

  //! g should be undirect
  template <bool with_deg>
  CEXP v_bcc(alist<with_deg> CR g) NE : dfn(g.size()), low(g.size()) {
    if CEXP (get_vcut) vcut = vecb(g.size());
    if CEXP (get_ecut) ecut.reserve(g.size());
    vecu stk;
    u32 cnt = 0, start;
    auto tarjan = [&](auto&& f, u32 u, u32 fa) -> void {
      u32 son = 0;
      bool ecut_flag = false;
      low[u] = dfn[u] = ++cnt;
      if CEXP (get_belongs) stk.push_back(u);
      for (auto v : g[u])
        if (!dfn[v]) {
          ++son, f(f, v, u), low[u] = min(low[u], low[v]);
          if CEXP (get_ecut) {
            if (low[v] > dfn[u]) ecut.emplace_back(v, u);
          } else {
            if (low[v] >= dfn[u]) {
              if CEXP (get_vcut)
                if (u != start) vcut[u] = true;
              if CEXP (get_belongs) {
                vecu res;
                u32 p;
                do res.push_back(p = stk.back()), stk.pop_back();
                while (v != p);
                res.push_back(u), belongs.emplace_back(std::move(res));
              }
            }
          }
        } else {
          if CEXP (get_ecut) {
            if (v != fa || ecut_flag) low[u] = min(low[u], dfn[v]);
            else ecut_flag = true;
          } else if (v != fa) low[u] = min(low[u], dfn[v]);
        }
      if CEXP (get_vcut)
        if (u == start && son >= 2) vcut[u] = true;
      if CEXP (get_belongs)
        if (!~fa && !son) belongs.push_back({u});
    };
    flt_ (u32, i, 0, g.size())
      if (!dfn[i]) tarjan(tarjan, start = i, -1_u32);
  }
};

}  // namespace tifa_libs::graph

#endif