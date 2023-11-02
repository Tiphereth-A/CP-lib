#ifndef TIFA_LIBS_TREE_LCA_HLD
#define TIFA_LIBS_TREE_LCA_HLD

#include "tree.hpp"

namespace tifa_libs::graph {

template <class VW = void, class EW = void>
class lca_hld {
  tree<VW, EW>& tr;

 public:
  lca_hld(tree<VW, EW>& tr) : tr(tr) {
    tr.template reset_dfs_info<s_dep | s_fa>();
    tr.template reset_top<true>();
  }

  u32 operator()(u32 u, u32 v) const {
    while (tr.top[u] != tr.top[v]) tr.dep[tr.top[u]] < tr.dep[tr.top[v]] ? v = tr.fa[tr.top[v]] : u = tr.fa[tr.top[u]];
    return tr.dep[u] > tr.dep[v] ? v : u;
  }
  ptt<vec<ptt<u32>>> getchain(u32 u, u32 v) {
    u32 lca = (*this)(u, v);
    vec<ptt<u32>> retu, retv;
    while (tr.top[u] != tr.top[lca]) {
      retu.emplace_back(u, tr.top[u]), u = tr.fa[tr.top[u]];
    }
    retu.emplace_back(u, lca);
    while (tr.top[v] != tr.top[lca]) {
      retv.emplace_back(tr.top[v], v), v = tr.fa[tr.top[v]];
    }
    if (v != lca) retv.emplace_back(tr.maxson[lca], v);
    std::reverse(retv.begin(), retv.end());
    return {retu, retv};
  }
};

}  // namespace tifa_libs::graph

#endif