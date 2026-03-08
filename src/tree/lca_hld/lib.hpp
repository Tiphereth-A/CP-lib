#pragma once

#include "../dfs/info/lib.hpp"
#include "../dfs/top/lib.hpp"

namespace tifa_libs::graph {

template <tree_c G>
struct lca_hld {
  using tree_info_t = graph::tree_dfs_info<G, graph::tdi_dfn, graph::tdi_maxson, graph::tdi_dep, graph::tdi_fa>;
  tree_info_t info;
  vecu top;

  CEXP lca_hld(G CR tr) : info{tr} { top = tree_top(tr, info.dfn, info.maxson); }

  CEXP u32 operator()(u32 u, u32 v) CNE {
    while (top[u] != top[v]) info.dep[top[u]] < info.dep[top[v]] ? v = info.fa[top[v]] : u = info.fa[top[u]];
    retif_((info.dep[u] > info.dep[v]), v, u);
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
