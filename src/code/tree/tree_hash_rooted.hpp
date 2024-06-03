#ifndef TIFALIBS_TREE_TREE_HASH_ROOTED
#define TIFALIBS_TREE_TREE_HASH_ROOTED

#include "../graph/dfs.hpp"
#include "tree.hpp"

namespace tifa_libs::graph {

template <class Hash, u64 OFFSET = 1>
CEXP vecuu tree_hash_rooted(cT_(tree) tr, Hash &&hasher) {
  vecuu hash(tr.g.size(), OFFSET);
  return dfs(tr, tr.root, fn_0, fn_0, [&](u32 to, u32 u, u32 = 1) { hash[u] += hasher(hash[to]); }, fn_0), hash;
}

}  // namespace tifa_libs::graph

#endif