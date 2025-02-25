#ifndef TIFALIBS_TREE_LCA_HLD
#define TIFALIBS_TREE_LCA_HLD

#include "dfs_info.hpp"
#include "tree.hpp"
#include "tree_top.hpp"

namespace tifa_libs::graph {

struct lca_hld {
  using tree_info_t = graph::tree_dfs_info<graph::tree, graph::tdi_dfn, graph::tdi_maxson, graph::tdi_dep, graph::tdi_fa>;
  tree_info_t CR info;
  vecu top;

  CEXP lca_hld(tree CR tr, tree_info_t CR info) : info{info} { top = tree_top(tr, info.dfn, info.maxson); }

  CEXP u32 operator()(u32 u, u32 v) CNE {
    while (top[u] != top[v]) info.dep[top[u]] < info.dep[top[v]] ? v = info.fa[top[v]] : u = info.fa[top[u]];
    return info.dep[u] > info.dep[v] ? v : u;
  }
  CEXP ptt<vecptu> getchain(u32 u, u32 v) NE {
    u32 lca = (*this)(u, v);
    vecptu retu, retv;
    while (top[u] != top[lca]) retu.emplace_back(u, top[u]), u = info.fa[top[u]];
    retu.emplace_back(u, lca);
    while (top[v] != top[lca]) retv.emplace_back(top[v], v), v = info.fa[top[v]];
    if (v != lca) retv.emplace_back(info.maxson[lca], v);
    reverse(retv);
    return {retu, retv};
  }
};

}  // namespace tifa_libs::graph

#endif