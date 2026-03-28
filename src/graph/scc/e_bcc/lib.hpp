#pragma once

#include "../../ds/eog/lib.hpp"

namespace tifa_libs {

struct e_bcc {
  vecu dfn, low;
  vvecu belongs;

  //! g should be undirect
  template <class T, class... Info>
  CEXP e_bcc(eog<T, Info...> CR g) NE : dfn(g.vsize()), low(g.vsize()) {
    vecu stk;
    u32 tot = 0;
    auto tarjan = [&](auto&& f, u32 u, u32 fa) -> void {
      dfn[u] = low[u] = ++tot;
      stk.push_back(u);
      bool skipped_parent = false;
      g.foreach(u, [&](u32 v) {
        if (!dfn[v]) f(f, v, u), low[u] = min(low[u], low[v]);
        else if (v != fa || std::exchange(skipped_parent, true)) low[u] = min(low[u], dfn[v]);
      });
      if (low[u] == dfn[u]) {
        vecu res;
        u32 p;
        do res.push_back(p = stk.back()), stk.pop_back();
        while (u != p);
        belongs.emplace_back(std::move(res));
      }
    };
    flt_ (u32, i, 0, g.vsize())
      if (!dfn[i]) tarjan(tarjan, i, -1_u32);
  }
};

}  // namespace tifa_libs
