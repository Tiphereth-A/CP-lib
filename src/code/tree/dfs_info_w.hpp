#ifndef TIFALIBS_TREE_DFS_INFO_W
#define TIFALIBS_TREE_DFS_INFO_W

#include "../graph/dfs.hpp"
#include "dfs_info_mask.hpp"
#include "treew.hpp"

namespace tifa_libs::graph {

template <class T>
struct tree_dfs_info_w {
  vec<u32> dfn, sz, fa, dep, maxson, maxdfn, euler;
  vvec<u32> go;
  vec<T> dis;

  template <int state>
  tree_dfs_info_w& reset_dfs_info(treew<T> const& tree) {
    u32 n = (u32)tree.g.size();
    if constexpr (state & (td_dfn | td_maxdfn | td_euler)) dfn = vec<u32>(n);
    if constexpr (state & (td_sz | td_maxson)) sz = vec<u32>(n);
    if constexpr (state & td_fa) fa = vec<u32>(n);
    if constexpr (state & td_dep) dep = vec<u32>(n);
    if constexpr (state & td_maxson) maxson = vec<u32>(n, n);
    if constexpr (state & td_maxdfn) maxdfn = vec<u32>(n);
    if constexpr (state & td_euler) euler = vec<u32>(n);
    if constexpr (state & td_go) go = vec<vec<u32>>(n, vec<u32>(21u, n));
    if constexpr (state & tdw_dis) dis = vec<T>(n);

    u32 cnt = 0;

    dfs(
        tree, tree.root,
        [&](u32 u, u32 f) {
          if constexpr (state & (td_dfn | td_maxdfn | td_euler)) dfn[u] = cnt++;
          if constexpr (state & (td_sz | td_maxson)) sz[u] = 1;
          if constexpr (state & td_fa) fa[u] = f;
          if constexpr (state & td_euler) euler[u] = cnt;
          if constexpr (state & td_go) {
            go[u][0] = f;
            for (u32 i = 1; i <= 20u && go[u][i - 1] < n; i++) go[u][i] = go[go[u][i - 1]][i - 1];
          }
        },
        [&](u32 to, T const& w, u32 u) {
          if constexpr (state & td_dep) dep[to] = dep[u] + 1;
          if constexpr (state & tdw_dis) dis[to] = dis[u] + w;
        },
        [&](u32 to, T const&, u32 u) {
          if constexpr (state & (td_sz | td_maxson)) sz[u] += sz[to];
          if constexpr (state & td_maxson)
            if (maxson[u] == n || sz[to] > sz[maxson[u]]) maxson[u] = to;
        },
        [&](u32 u, u32) {
          if constexpr (state & td_maxdfn) maxdfn[u] = cnt;
        });
    return *this;
  }
};

}  // namespace tifa_libs::graph

#endif