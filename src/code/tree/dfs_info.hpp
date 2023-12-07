#ifndef TIFALIBS_TREE_DFS_INFO
#define TIFALIBS_TREE_DFS_INFO

#include "../graph/dfs.hpp"
#include "tree.hpp"

namespace tifa_libs::graph {

enum dfs_info_state {
  dis_dfn = 1,
  dis_sz = 2,
  dis_fa = 4,
  dis_dep = 8,
  dis_maxson = 16,
  dis_maxdfn = 32,
  dis_euler = 64,
  dis_go = 128
};

struct tree_dfs_info {
  vec<u32> dfn, sz, fa, dep, maxson, maxdfn, euler;
  vvec<u32> go;

  template <int state>
  tree_dfs_info& reset_dfs_info(tree const& tree) {
    u32 n = (u32)tree.g.size();
    if constexpr (state & (dis_dfn | dis_maxdfn | dis_euler)) dfn = vec<u32>(n);
    if constexpr (state & (dis_sz | dis_maxson)) sz = vec<u32>(n);
    if constexpr (state & dis_fa) fa = vec<u32>(n);
    if constexpr (state & dis_dep) dep = vec<u32>(n);
    if constexpr (state & dis_maxson) maxson = vec<u32>(n, n);
    if constexpr (state & dis_maxdfn) maxdfn = vec<u32>(n);
    if constexpr (state & dis_euler) euler = vec<u32>(n);
    if constexpr (state & dis_go) go = vec<vec<u32>>(n, vec<u32>(21u, n));

    u32 cnt = 0;

    dfs(
        tree, tree.root,
        [&](u32 u, u32 f) {
          if constexpr (state & (dis_dfn | dis_maxdfn | dis_euler)) dfn[u] = cnt++;
          if constexpr (state & (dis_sz | dis_maxson)) sz[u] = 1;
          if constexpr (state & dis_fa) fa[u] = f;
          if constexpr (state & dis_euler) euler[u] = cnt;
          if constexpr (state & dis_go) {
            go[u][0] = f;
            for (u32 i = 1; i <= 20u && go[u][i - 1] < n; i++) go[u][i] = go[go[u][i - 1]][i - 1];
          }
        },
        [&](u32 to, u32 u) {
          if constexpr (state & dis_dep) dep[to] = dep[u] + 1;
        },
        [&](u32 to, u32 u) {
          if constexpr (state & (dis_sz | dis_maxson)) sz[u] += sz[to];
          if constexpr (state & dis_maxson)
            if (maxson[u] == n || sz[to] > sz[maxson[u]]) maxson[u] = to;
        },
        [&](u32 u, u32) {
          if constexpr (state & dis_maxdfn) maxdfn[u] = cnt;
        });
    return *this;
  }
};

}  // namespace tifa_libs::graph

#endif