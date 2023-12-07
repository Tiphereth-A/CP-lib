#ifndef TIFALIBS_TREE_DIAM
#define TIFALIBS_TREE_DIAM

#include "dfs_info.hpp"
#include "dfs_info_w.hpp"

namespace tifa_libs::graph {

// {u, v, diam}
template <class G>
auto tree_diam(G &tree) {
  using Tinfo = std::conditional_t<std::is_base_of_v<alist, G>, tree_dfs_info, tree_dfs_info_w<typename G::weight_type>>;
  auto _ = tree.root;
  auto d = Tinfo().template reset_dfs_info<td_dis>(tree).dis;
  u32 u = tree.root = (u32)std::distance(d.begin(), std::max_element(d.begin(), d.end()));
  d = Tinfo().template reset_dfs_info<td_dis>(tree).dis;
  u32 v = (u32)std::distance(d.begin(), std::max_element(d.begin(), d.end()));
  tree.root = _;
  return std::make_tuple(u, v, d[v]);
}

}  // namespace tifa_libs::graph

#endif