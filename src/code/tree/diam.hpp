#ifndef TIFALIBS_TREE_DIAM
#define TIFALIBS_TREE_DIAM

#include "dfs_info.hpp"

namespace tifa_libs::graph {

// {u, v, diam}
template <class G>
CEXP auto tree_diam(G& tree) {
  auto _ = tree.root;
  tree_dfs_info<G> info;
  auto d = info.template reset_dfs_info<td_dis>(tree).dis;
  const u32 u = tree.root = u32(std::ranges::max_element(d) - d.begin());
  d = info.template reset_dfs_info<td_dis>(tree).dis;
  const u32 v = u32(std::ranges::max_element(d) - d.begin());
  tree.root = _;
  return std::make_tuple(u, v, d[v]);
}

// diam
template <class G>
CEXP auto tree_diam_d(G CR tree) {
  using T = TPN G::weight_type;
  vec<T> mdis(tree.g.size());
  T d = 0;
  dfs(
      tree, tree.root, fn_0, fn_0,
      [&](u32 to, u32 u, cT_(T) w = 1) {
        d = max(d, mdis[u] + mdis[to] + w);
        mdis[u] = max(mdis[u], mdis[to] + w);
      },
      fn_0);
  return d;
}

}  // namespace tifa_libs::graph

#endif