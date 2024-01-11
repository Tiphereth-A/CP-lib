#ifndef TIFALIBS_TREE_TREE_HASH_ROOTED
#define TIFALIBS_TREE_TREE_HASH_ROOTED

#include "../graph/dfs.hpp"
#include "tree.hpp"

namespace tifa_libs::graph {

template <class Hash, u64 OFFSET = 1>
constexpr vec<u64> tree_hash_rooted(tree const &tr, Hash &&hasher) {
  vec<u64> hash(tr.g.size(), OFFSET);
  dfs(
      tr, tr.root,
      [](u32, u32) {},
      [](u32, u32, u32 = 1) {},
      [&](u32 to, u32 u, u32 = 1) {
        hash[u] += hasher(hash[to]);
      },
      [](u32, u32) {});
  return hash;
}

}  // namespace tifa_libs::graph

#endif