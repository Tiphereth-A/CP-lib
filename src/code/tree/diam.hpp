#ifndef TIFALIBS_TREE_DIAM
#define TIFALIBS_TREE_DIAM

#include "../graph/dfs.hpp"

namespace tifa_libs::graph {

// {u, v, diam}
template <class G>
constexpr auto tree_diam(G const& tree) {
  using T = typename G::weight_type;

  u32 n = (u32)tree.g.size();
  vec<T> mdis(n), mdis2(n);
  vec<u32> midx(n), midx2;
  std::iota(midx.begin(), midx.end(), 0), midx2 = midx;

  dfs(
      tree, tree.root,
      [](u32, u32) {},
      [](u32, u32, T const& = 1) {},
      [&](u32 to, u32 u, T const& w = 1) {
        if (T _ = mdis[to] + w; _ > mdis[u]) {
          mdis2[u] = mdis[u], midx2[u] = midx[u];
          mdis[u] = _, midx[u] = midx[to];
        } else if (_ > mdis2[u]) {
          mdis2[u] = _, midx2[u] = midx2[to];
          if (midx[u] == u) midx[u] = midx[to];
        }
      },
      [](u32, u32) {});

  u32 u = midx[0], v = midx2[0];
  T d = mdis[0] + mdis2[0];
  for (u32 i = 1; i < n; ++i)
    if (d < mdis[i] + mdis2[i]) u = midx[i], v = midx2[i], d = mdis[i] + mdis2[i];
  return std::make_tuple(u, v, d);
}

}  // namespace tifa_libs::graph

#endif