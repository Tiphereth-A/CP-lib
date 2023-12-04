#ifndef TIFALIBS_TREE_LCA_HLD
#define TIFALIBS_TREE_LCA_HLD

#include "dfs_info.hpp"

namespace tifa_libs::graph {

struct lca_hld {
  tree_dfs_info info;

  lca_hld(tree& tr) { info.reset_dfs_info<s_dep | s_fa>(tr).reset_top<true>(tr); }

  u32 operator()(u32 u, u32 v) const {
    while (info.top[u] != info.top[v]) info.dep[info.top[u]] < info.dep[info.top[v]] ? v = info.fa[info.top[v]] : u = info.fa[info.top[u]];
    return info.dep[u] > info.dep[v] ? v : u;
  }
  ptt<vec<ptt<u32>>> getchain(u32 u, u32 v) {
    u32 lca = (*this)(u, v);
    vec<ptt<u32>> retu, retv;
    while (info.top[u] != info.top[lca]) {
      retu.emplace_back(u, info.top[u]), u = info.fa[info.top[u]];
    }
    retu.emplace_back(u, lca);
    while (info.top[v] != info.top[lca]) {
      retv.emplace_back(info.top[v], v), v = info.fa[info.top[v]];
    }
    if (v != lca) retv.emplace_back(info.maxson[lca], v);
    std::reverse(retv.begin(), retv.end());
    return {retu, retv};
  }
};

}  // namespace tifa_libs::graph

#endif