#pragma once

#include "../../ds/lib.hpp"

namespace tifa_libs {

// @return centroid, at MOST 2
CEXP vecu tree_centroid(tree_c auto CR tr) NE {
  vecu sz(tr.vsize()), ans;
  auto dfs = [&](auto&& dfs, u32 now, u32 fa = -1_u32) NE -> void {
    u32 max_sz = 0;
    for (sz[now] = 1; u32 to : tr[now])
      if (to != fa) dfs(dfs, to, now), sz[now] += sz[to], max_sz = max(max_sz, sz[to]);
    if (max(max_sz, tr.vsize() - sz[now]) <= tr.vsize() / 2) ans.push_back(now);
  };
  dfs(dfs, tr.root);
  return ans;
}

}  // namespace tifa_libs
