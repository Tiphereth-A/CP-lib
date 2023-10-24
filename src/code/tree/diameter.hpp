#ifndef TIFA_LIBS_TREE_DIAMETER
#define TIFA_LIBS_TREE_DIAMETER

#include "tree.hpp"

namespace tifa_libs::graph {

// {u, v, diam}
inline pt3<u32> tree_diameter(tree<void> &tr) {
  auto _ = tr.rt;
  tr.template reset_dfs_info<s_dep>();
  u32 u = tr.rt = (u32)std::distance(tr.dep.begin(), std::max_element(tr.dep.begin(), tr.dep.end()));
  tr.template reset_dfs_info<s_dep>();
  u32 v = (u32)std::distance(tr.dep.begin(), std::max_element(tr.dep.begin(), tr.dep.end()));
  tr.rt = _;
  return {u, v, tr.dep[v]};
}

}  // namespace tifa_libs::graph

#endif