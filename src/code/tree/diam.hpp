#ifndef TIFA_LIBS_TREE_DIAM
#define TIFA_LIBS_TREE_DIAM

#include "dfs_info.hpp"
#include "dfs_info_w.hpp"

namespace tifa_libs::graph {

// {u, v, diam}
template <class G>
inline auto tree_diam(G &tree) {
  constexpr bool F = std::is_base_of_v<alist, G>;
  auto _ = tree.root;
  vec<std::conditional_t<F, u32, typename G::weight_type>> d;
  if constexpr (F) d = tree_dfs_info().reset_dfs_info<s_dep>(tree).dep;
  else d = tree_dfs_info_w<typename G::weight_type>().template reset_dfs_info<dws_dis>(tree).dis;
  u32 u = tree.root = (u32)std::distance(d.begin(), std::max_element(d.begin(), d.end()));
  if constexpr (F) d = tree_dfs_info().reset_dfs_info<s_dep>(tree).dep;
  else d = tree_dfs_info_w<typename G::weight_type>().template reset_dfs_info<dws_dis>(tree).dis;
  u32 v = (u32)std::distance(d.begin(), std::max_element(d.begin(), d.end()));
  tree.root = _;
  return std::make_tuple(u, v, d[v]);
}

}  // namespace tifa_libs::graph

#endif