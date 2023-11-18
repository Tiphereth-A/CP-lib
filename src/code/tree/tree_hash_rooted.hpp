#ifndef TIFA_LIBS_TREE_TREE_HASH_ROOTED
#define TIFA_LIBS_TREE_TREE_HASH_ROOTED

#include "../graph/dfs.hpp"
#include "tree.hpp"

namespace tifa_libs::graph {

template <class Hash, u64 OFFSET = 1>
vec<u64> tree_hash_rooted(tree const &tr, Hash &&hasher) {
  vec<u64> hash(tr.g.size());
  dfs(
      tr, tr.root,
      [&](u32 u, u32) {
        hash[u] = OFFSET;
      },
      [](u32, u32) {},
      [&](u32 to, u32 u) {
        hash[u] += hasher(hash[to]);
      });
  return hash;
}

}  // namespace tifa_libs::graph

#endif