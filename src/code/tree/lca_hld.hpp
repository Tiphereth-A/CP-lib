#ifndef TIFA_LIBS_TREE_LCA_HLD
#define TIFA_LIBS_TREE_LCA_HLD

#include "tree.hpp"

namespace tifa_libs::graph {

template <class T = void>
class lca_hld {
  tree<T>& tr;

 public:
  lca_hld(tree<T>& tr) : tr(tr) {
    tr.template reset_dfs_info<s_dep | s_fa>();
    tr.template reset_top<true>();
  }

  u32 operator()(u32 u, u32 v) const {
    while (tr.top[u] != tr.top[v]) tr.dep[tr.top[u]] < tr.dep[tr.top[v]] ? v = tr.fa[tr.top[v]] : u = tr.fa[tr.top[u]];
    return tr.dep[u] > tr.dep[v] ? v : u;
  }
};

}  // namespace tifa_libs::graph

#endif