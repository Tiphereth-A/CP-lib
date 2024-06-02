#ifndef TIFALIBS_TREE_TREE_TOP
#define TIFALIBS_TREE_TREE_TOP

#include "dfs_info.hpp"

namespace tifa_libs::graph {

template <class G, bool need_dfn = false>
CEXP vecu tree_top(G CR tr, tree_dfs_info<G> &info) {
  u32 n = (u32)tr.g.size();
  if (info.maxson.empty()) info.template reset_dfs_info<td_maxson>(tr);
  if CEXP (need_dfn) info.dfn = vecu(n);
  vecu top(n, n);
  u32 cnt = 0;
  auto f = [&](auto &&f, u32 u, u32 top_) -> void {
    if CEXP (need_dfn) info.dfn[u] = cnt++;
    if (top[u] = top_; info.maxson[u] == tr.g.size()) return;
    for (f(f, info.maxson[u], top_); auto v : tr.g[u])
      if CEXP (is_alist<G>) {
        if (top[v] == tr.g.size()) f(f, v, v);
      } else if (top[v.first] == tr.g.size()) f(f, v.first, v.first);
  };
  return f(f, tr.root, tr.root), top;
}

}  // namespace tifa_libs::graph

#endif