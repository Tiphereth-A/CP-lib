#ifndef TIFALIBS_TREE_CENTROID
#define TIFALIBS_TREE_CENTROID

#include "tree.hpp"

namespace tifa_libs::graph {

// @return centroid, at MOST 2
CEXP vecu tree_centroid(cT_(tree) tr) {
  vecu sz(tr.g.size()), ans;
  auto dfs = [&](auto &&dfs, u32 now, u32 fa = -1_u32) -> void {
    u32 max_sz = 0;
    for (sz[now] = 1; u32 to : tr.g[now])
      if (to != fa) dfs(dfs, to, now), sz[now] += sz[to], max_sz = max(max_sz, sz[to]);
    if (max(max_sz, (u32)tr.g.size() - sz[now]) <= tr.g.size() / 2) ans.push_back(now);
  };
  return dfs(dfs, tr.root), ans;
}

}  // namespace tifa_libs::graph

#endif