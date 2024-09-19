#ifndef TIFALIBS_TREE_TREE_TOP
#define TIFALIBS_TREE_TREE_TOP

#include "dfs_info.hpp"

namespace tifa_libs::graph {

template <tree_c G, bool need_dfn = false>
CEXP vecu tree_top(G CR tr, tree_dfs_info<G> &info) {
  u32 n = (u32)tr.size();
  if (info.maxson.empty()) info.template reset_dfs_info<td_maxson>(tr);
  if CEXP (need_dfn) info.dfn = vecu(n);
  vecu top(n, n);
  u32 cnt = 0;
  auto f = [&](auto &&f, u32 u, u32 top_) -> void {
    if CEXP (need_dfn) info.dfn[u] = cnt++;
    if (top[u] = top_; info.maxson[u] == tr.size()) return;
    for (f(f, info.maxson[u], top_); auto v : tr[u])
      if (top[(u32)v] == tr.size()) f(f, (u32)v, (u32)v);
  };
  return f(f, tr.root, tr.root), top;
}

}  // namespace tifa_libs::graph

#endif