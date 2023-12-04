#ifndef TIFALIBS_TREE_CENTROID
#define TIFALIBS_TREE_CENTROID

#include "tree.hpp"

namespace tifa_libs::graph {

namespace tree_centroid_impl_ {

inline void dfs_(tree const &tr, vec<u32> &sz, vec<u32> &ans, u32 now, u32 fa) {
  sz[now] = 1;
  u32 max_sz = 0;
  for (u32 to : tr.g[now])
    if (to != fa) {
      dfs_(tr, sz, ans, to, now);
      sz[now] += sz[to];
      max_sz = std::max(max_sz, sz[to]);
    }
  if (std::max(max_sz, (u32)tr.g.size() - sz[now]) <= tr.g.size() / 2) ans.push_back(now);
}

}  // namespace tree_centroid_impl_

inline vec<u32> tree_centroid(tree const &tr) {
  vec<u32> sz(tr.g.size()), ans;
  tree_centroid_impl_::dfs_(tr, sz, ans, tr.root, -1_u32);
  return ans;
}

}  // namespace tifa_libs::graph

#endif