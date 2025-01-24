#ifndef TIFALIBS_TREE_TREE_HASH_ROOTED
#define TIFALIBS_TREE_TREE_HASH_ROOTED

#include "tree.hpp"

namespace tifa_libs::graph {

template <class Hash, u64 OFFSET = 1>
CEXP vecuu tree_hash_rooted(tree CR tr, Hash&& hasher) NE {
  vecuu hash(tr.g.size(), OFFSET);
  auto dfs = [&](auto&& dfs, u32 u, u32 fa) NE -> void {
    for (auto v : tr.g[u])
      if ((u32)v != fa) dfs(dfs, (u32)v, u), hash[u] += hasher(hash[v]);
  };
  dfs(dfs, tr.root, -1_u32);
  return hash;
}

}  // namespace tifa_libs::graph

#endif