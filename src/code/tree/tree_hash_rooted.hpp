#ifndef TIFA_LIBS_TREE_TREE_HASH_ROOTED
#define TIFA_LIBS_TREE_TREE_HASH_ROOTED

#include "tree.hpp"

namespace tifa_libs::graph {

namespace tree_hash_rooted_impl_ {

template <class EW, class Hash, u64 OFFSET>
void dfs_(tree<void, EW> const &tr, Hash hasher, vec<u64> &hash, u32 now, u32 fa) {
  hash[now] = OFFSET;
  for (auto v : tr[now])
    if (v.to != fa) {
      dfs_<EW, Hash, OFFSET>(tr, hasher, hash, v.to, now);
      hash[now] += hasher(hash[v.to]);
    }
}

}  // namespace tree_hash_rooted_impl_

template <class EW, class Hash, u64 OFFSET = 1>
inline vec<u64> tree_hash_rooted(tree<void, EW> const &tr, Hash hasher) {
  vec<u64> ans(tr.v_size());
  tree_hash_rooted_impl_::dfs_<EW, Hash, OFFSET>(tr, hasher, ans, tr.rt, tr.v_size());
  return ans;
}

}  // namespace tifa_libs::graph

#endif