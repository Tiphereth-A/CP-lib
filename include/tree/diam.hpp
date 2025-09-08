#ifndef TIFALIBS_TREE_DIAM
#define TIFALIBS_TREE_DIAM

#include "dfs_info.hpp"

namespace tifa_libs::graph {

// {u, v, diam}
template <tree_c G>
CEXP auto tree_diam(G& tree) NE {
  auto _ = tree.root;
  auto d = tree_dfs_info<G, tdi_dis<G>>(tree).dis;
  const u32 u = tree.root = u32(max_element(d) - begin(d));
  d = tree_dfs_info<G, tdi_dis<G>>(tree).dis;
  const u32 v = u32(max_element(d) - begin(d));
  tree.root = _;
  return std::make_tuple(u, v, d[v]);
}
// diam
template <tree_c G>
CEXP auto tree_diam_d(G CR tree) NE {
  using T = TPN G::w_t;
  vec<T> mdis(tree.size());
  T d = 0;
  auto dfs = [&](auto&& dfs, u32 u, u32 fa) NE -> void {
    if CEXP (alistw_c<G>) {
      for (auto [v, w] : tree.g[u])
        if (v != fa) dfs(dfs, v, u), d = max(d, mdis[u] + mdis[v] + w), mdis[u] = max(mdis[u], mdis[v] + w);
      ;
    } else
      for (auto v : tree.g[u])
        if ((u32)v != fa) dfs(dfs, (u32)v, u), d = max(d, mdis[u] + mdis[v] + 1), mdis[u] = max(mdis[u], mdis[v] + 1);
  };
  dfs(dfs, tree.root, -1_u32);
  return d;
}

}  // namespace tifa_libs::graph

#endif