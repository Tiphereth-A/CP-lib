#ifndef TIFALIBS_TREE_TREE_TOP
#define TIFALIBS_TREE_TREE_TOP

#include "dfs_info.hpp"
#include "dfs_info_w.hpp"

namespace tifa_libs::graph {

namespace tree_top_impl_ {

template <class G, class Tinfo, bool need_dfn = false>
void tree_top_(G const &tr, Tinfo &info, u32 u, u32 top_, u32 &cnt, vec<u32> &top) {
  if constexpr (need_dfn) info.dfn[u] = cnt++;
  top[u] = top_;
  if (info.maxson[u] == tr.g.size()) return;
  tree_top_(tr, info, info.maxson[u], top_, top);
  for (u32 to : tr.g[u])
    if (top[to] == tr.g.size()) dfs_top_(tr, info, to, to, top);
}

}  // namespace tree_top_impl_

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
  tree_top_impl_::tree_top_(tr, info, tr.root, tr.root, cnt, top);
  return top;
}

}  // namespace tifa_libs::graph

#endif