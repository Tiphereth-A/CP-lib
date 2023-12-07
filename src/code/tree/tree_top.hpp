#ifndef TIFALIBS_TREE_TREE_TOP
#define TIFALIBS_TREE_TREE_TOP

#include "dfs_info.hpp"
#include "dfs_info_w.hpp"

namespace tifa_libs::graph {

template <class G, bool need_dfn = false, class Tinfo = std::conditional_t<std::is_base_of_v<alist, G>, tree_dfs_info, tree_dfs_info_w<typename G::weight_type>>>
vec<u32> tree_top(G const &tr, Tinfo &info) {
  u32 n = (u32)tr.g.size();
  if (info.maxson.empty()) {
    if constexpr (std::is_base_of_v<alist, G>) info.template reset_dfs_info<dis_maxson>(tr);
    else info.template reset_dfs_info<diws_maxson>(tr);
  }
  if constexpr (need_dfn) info.dfn = vec<u32>(n);

  vec<u32> top(n, n);
  u32 cnt = 0;
  auto dfs = [&](auto &&dfs, u32 u, u32 top_) -> void {
    if constexpr (need_dfn) info.dfn[u] = cnt++;
    top[u] = top_;
    if (info.maxson[u] == tr.g.size()) return;
    dfs(dfs, info.maxson[u], top_);
    for (u32 to : tr.g[u])
      if (top[to] == tr.g.size()) dfs(dfs, to, to);
  };

  dfs(dfs, tr.root, tr.root);
  return top;
}

}  // namespace tifa_libs::graph

#endif