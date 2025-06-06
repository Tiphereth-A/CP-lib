#ifndef TIFALIBS_TREE_TREE_SUMVW
#define TIFALIBS_TREE_TREE_SUMVW

#include "../util/alias_others.hpp"
#include "../util/traits_graph.hpp"

namespace tifa_libs::graph {

template <tree_c G, class T>
CEXP vec<T> tree_sumvw(G CR tr, vec<T> CR v_weight) NE {
  vec<T> sumvw = v_weight;
  auto dfs = [&](auto&& dfs, u32 u, u32 fa) NE -> void {
    if CEXP (alistw_c<G>) {
      for (auto [v, w] : tr.g[u])
        if (v != fa) dfs(dfs, v, u), sumvw[u] += sumvw[v];
      ;
    } else
      for (auto v : tr.g[u])
        if ((u32)v != fa) dfs(dfs, (u32)v, u), sumvw[u] += sumvw[v];
  };
  dfs(dfs, tr.root, -1_u32);
  return sumvw;
}

}  // namespace tifa_libs::graph

#endif