#pragma once

#include "../../../util/alias/others/lib.hpp"
#include "../../../util/traits/graph/lib.hpp"

namespace tifa_libs::graph {

template <tree_c G, bool need_dfn = false>
CEXP vecu tree_top(G CR tr, std::conditional_t<need_dfn, vecu&, spnu> dfn, spnu maxson) NE {
  u32 n = (u32)tr.size();
  if CEXP (need_dfn) dfn = vecu(n);
  vecu top(n, n);
  u32 cnt = 0;
  auto f = [&](auto&& f, u32 u, u32 top_) NE -> void {
    if CEXP (need_dfn) dfn[u] = cnt++;
    if (top[u] = top_; maxson[u] == tr.size()) return;
    if CEXP (alistw_c<G>) {
      for (f(f, maxson[u], top_); auto [v, w] : tr[u])
        if (top[v] == tr.size()) f(f, v, v);
    } else
      for (f(f, maxson[u], top_); auto v : tr[u])
        if (top[(u32)v] == tr.size()) f(f, (u32)v, (u32)v);
  };
  f(f, tr.root, tr.root);
  return top;
}

}  // namespace tifa_libs::graph
