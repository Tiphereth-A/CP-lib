#ifndef TIFALIBS_TREE_TREE_TOP
#define TIFALIBS_TREE_TREE_TOP

#include "dfs_info.hpp"

namespace tifa_libs::graph {

template <class G, bool need_dfn = false>
constexpr vec<u32> tree_top(G const &tr, tree_dfs_info<G> &info) {
  u32 n = (u32)tr.g.size();
  if (info.maxson.empty()) info.template reset_dfs_info<td_maxson>(tr);
  if constexpr (need_dfn) info.dfn = vec<u32>(n);

  vec<u32> top(n, n);
  u32 cnt = 0;
  auto dfs = [&](auto &&dfs, u32 u, u32 top_) -> void {
    if constexpr (need_dfn) info.dfn[u] = cnt++;
    top[u] = top_;
    if (info.maxson[u] == tr.g.size()) return;
    dfs(dfs, info.maxson[u], top_);
    for (auto v : tr.g[u])
      if constexpr (std::is_base_of_v<alist, G>) {
        if (top[v] == tr.g.size()) dfs(dfs, v, v);
      } else {
        if (top[v.first] == tr.g.size()) dfs(dfs, v.first, v.first);
      }
  };

  dfs(dfs, tr.root, tr.root);
  return top;
}

}  // namespace tifa_libs::graph

#endif