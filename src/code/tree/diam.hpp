#ifndef TIFALIBS_TREE_DIAM
#define TIFALIBS_TREE_DIAM

#include "dfs_info.hpp"

namespace tifa_libs::graph {

// {u, v, diam}
template <class G>
constexpr auto tree_diam(G &tree) {
  auto _ = tree.root;
  tree_dfs_info<G> info;
  auto d = info.template reset_dfs_info<td_dis>(tree).dis;
  u32 u = tree.root = (u32)std::distance(d.begin(), std::max_element(d.begin(), d.end()));
  d = info.template reset_dfs_info<td_dis>(tree).dis;
  u32 v = (u32)std::distance(d.begin(), std::max_element(d.begin(), d.end()));
  tree.root = _;
  return std::make_tuple(u, v, d[v]);
}

}  // namespace tifa_libs::graph

#endif