#ifndef TIFALIBS_TREE_DIAM
#define TIFALIBS_TREE_DIAM

#include "dfs_info.hpp"

namespace tifa_libs::graph {

// {u, v, diam}
template <class G>
constexpr auto tree_diam(G& tree) {
  auto _ = tree.root;
  tree_dfs_info<G> info;
  auto d = info.template reset_dfs_info<td_dis>(tree).dis;
  u32 u = tree.root = u32(std::ranges::max_element(d) - d.begin());
  d = info.template reset_dfs_info<td_dis>(tree).dis;
  u32 v = u32(std::ranges::max_element(d) - d.begin());
  tree.root = _;
  return std::make_tuple(u, v, d[v]);
}

// diam
template <class G>
constexpr auto tree_diam_d(G const& tree) {
  using T = typename G::weight_type;
  vec<T> mdis(tree.g.size());
  T d = 0;
  dfs(
      tree, tree.root, fn_0, fn_0,
      [&](u32 to, u32 u, T const& w = 1) {
        d = std::max(d, mdis[u] + mdis[to] + w);
        mdis[u] = std::max(mdis[u], mdis[to] + w);
      },
      fn_0);
  return d;
}

}  // namespace tifa_libs::graph

#endif