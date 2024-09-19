#ifndef TIFALIBS_TREE_DSU_ON_TREE
#define TIFALIBS_TREE_DSU_ON_TREE

#include "dfs_info.hpp"

namespace tifa_libs::graph {

// @param update(now): update data of node %now
// @param query(now): answer queries of subtree %now
// @param clear(now): reset data of node %now (if necesarry)
// @param reset(): reset data related to all (if necesarry)
template <tree_c G, class Fu, class Fq, class Fc, class Fr>
requires requires(Fu update, Fq query, Fc clear, Fr reset, u32 now) {
  update(now);
  query(now);
  clear(now);
  reset();
}
CEXP void dsu_on_tree(G CR tr, tree_dfs_info<G>& info, Fu&& update, Fq&& query, Fc&& clear, Fr&& reset) {
  if (info.dfn.empty() || info.maxson.empty() || info.maxdfn.empty() || info.euler.empty()) info.template reset_dfs_info<td_dfn | td_maxson | td_maxdfn | td_euler>(tr);
  auto f = [&](auto&& f, u32 now, u32 fa = -1_u32, bool keep = false) -> void {
    for (auto v : tr[now])
      if ((u32)v != fa && (u32)v != info.maxson[now]) f(f, (u32)v, now, false);
    if (info.sz[now] > 1) f(f, info.maxson[now], now, true);
    for (auto v : tr[now])
      if ((u32)v != fa && (u32)v != info.maxson[now])
        fle_ (u32, i, info.dfn[(u32)v], info.maxdfn[(u32)v]) update(info.euler[i]);
    update(now), query(now);
    if (!keep) {
      fle_ (u32, i, info.dfn[now], info.maxdfn[now]) clear(info.euler[i]);
      reset();
    }
    return;
  };
  f(f, tr.root);
}

}  // namespace tifa_libs::graph

#endif