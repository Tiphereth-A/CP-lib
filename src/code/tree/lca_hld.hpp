#ifndef TIFA_LIBS_TREE_LCA_HLD
#define TIFA_LIBS_TREE_LCA_HLD

#include "tree_dfs.hpp"

namespace tifa_libs::graph {

class lca_hld {
  vec<u32> fa, dep, top, maxson;

 public:
  template <class T>
  lca_hld(tree<T> const& tr) {
    tree_dfs<T, dfs_state::fa | dfs_state::dep | dfs_state::maxson>(tr, top, top, fa, dep, maxson);
    tree_dfs_top(tr, maxson, top);
  }

  u32 operator()(u32 u, u32 v) const {
    while (top[u] != top[v]) dep[top[u]] < dep[top[v]] ? v = fa[top[v]] : u = fa[top[u]];
    return dep[u] > dep[v] ? v : u;
  }
};

}  // namespace tifa_libs::graph

#endif