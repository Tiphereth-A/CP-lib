#ifndef TIFALIBS_TREE_DSU_ON_TREE
#define TIFALIBS_TREE_DSU_ON_TREE

#include "../util/traits.hpp"

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
CEXP void dsu_on_tree(G CR tr, spnu dfn, spnu sz, spnu maxson, spnu maxdfn, spnu euler, Fu&& update, Fq&& query, Fc&& clear, Fr&& reset) {
  auto f = [&](auto&& f, u32 now, u32 fa = -1_u32, bool keep = false) -> void {
    for (auto v : tr[now])
      if ((u32)v != fa && (u32)v != maxson[now]) f(f, (u32)v, now, false);
    if (sz[now] > 1) f(f, maxson[now], now, true);
    for (auto v : tr[now])
      if ((u32)v != fa && (u32)v != maxson[now])
        fle_ (u32, i, dfn[(u32)v], maxdfn[(u32)v]) update(euler[i]);
    update(now), query(now);
    if (!keep) {
      fle_ (u32, i, dfn[now], maxdfn[now]) clear(euler[i]);
      reset();
    }
    return;
  };
  f(f, tr.root);
}

}  // namespace tifa_libs::graph

#endif