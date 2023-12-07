#ifndef TIFALIBS_TREE_DFS_INFO_W
#define TIFALIBS_TREE_DFS_INFO_W

#include "../graph/dfs.hpp"
#include "treew.hpp"

namespace tifa_libs::graph {

enum dfs_info_w_state {
  diws_dfn = 1,
  diws_sz = 2,
  diws_fa = 4,
  diws_dep = 8,
  diws_maxson = 16,
  diws_maxdfn = 32,
  diws_euler = 64,
  diws_go = 128,
  diws_dis = 256
};

template <class T>
struct tree_dfs_info_w {
  vec<u32> dfn, sz, fa, dep, maxson, maxdfn, euler;
  vvec<u32> go;
  vec<T> dis;

  template <int state>
  tree_dfs_info_w& reset_dfs_info(treew<T> const& tree) {
    u32 n = (u32)tree.g.size();
    if constexpr (state & (diws_dfn | diws_maxdfn | diws_euler)) dfn = vec<u32>(n);
    if constexpr (state & (diws_sz | diws_maxson)) sz = vec<u32>(n);
    if constexpr (state & diws_fa) fa = vec<u32>(n);
    if constexpr (state & diws_dep) dep = vec<u32>(n);
    if constexpr (state & diws_maxson) maxson = vec<u32>(n, n);
    if constexpr (state & diws_maxdfn) maxdfn = vec<u32>(n);
    if constexpr (state & diws_euler) euler = vec<u32>(n);
    if constexpr (state & diws_go) go = vec<vec<u32>>(n, vec<u32>(21u, n));
    if constexpr (state & diws_dis) dis = vec<T>(n);

    u32 cnt = 0;

    dfs(
        tree, tree.root,
        [&](u32 u, u32 f) {
          if constexpr (state & (diws_dfn | diws_maxdfn | diws_euler)) dfn[u] = cnt++;
          if constexpr (state & (diws_sz | diws_maxson)) sz[u] = 1;
          if constexpr (state & diws_fa) fa[u] = f;
          if constexpr (state & diws_euler) euler[u] = cnt;
          if constexpr (state & diws_go) {
            go[u][0] = f;
            for (u32 i = 1; i <= 20u && go[u][i - 1] < n; i++) go[u][i] = go[go[u][i - 1]][i - 1];
          }
        },
        [&](u32 to, T const& w, u32 u) {
          if constexpr (state & diws_dep) dep[to] = dep[u] + 1;
          if constexpr (state & diws_dis) dis[to] = dis[u] + w;
        },
        [&](u32 to, T const&, u32 u) {
          if constexpr (state & (diws_sz | diws_maxson)) sz[u] += sz[to];
          if constexpr (state & diws_maxson)
            if (maxson[u] == n || sz[to] > sz[maxson[u]]) maxson[u] = to;
        },
        [&](u32 u, u32) {
          if constexpr (state & diws_maxdfn) maxdfn[u] = cnt;
        });
    return *this;
  }
};

}  // namespace tifa_libs::graph

#endif