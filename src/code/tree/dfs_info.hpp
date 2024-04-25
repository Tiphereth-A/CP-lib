#ifndef TIFALIBS_TREE_DFS_INFO
#define TIFALIBS_TREE_DFS_INFO

#include "../graph/dfs.hpp"

namespace tifa_libs::graph {

enum tree_dfs_info_mask {
  td_dfn = 1,
  td_sz = 2,
  td_fa = 4,
  td_dep = 8,
  td_maxson = 16,
  td_maxdfn = 32,
  td_euler = 64,
  td_go = 128,
  td_dis = 256
};

template <class G>
struct tree_dfs_info {
  using weight_type = TPN G::weight_type;

  vecu dfn, sz, fa, dep, maxson, maxdfn, euler;
  vvecu go;
  vec<weight_type> dis;

  template <int state>
  CEXP tree_dfs_info& reset_dfs_info(G CR tree) {
    u32 n = (u32)tree.g.size();
    if CEXP (state & td_dfn) dfn = vecu(n);
    if CEXP (state & (td_sz | td_maxson)) sz = vecu(n);
    if CEXP (state & td_fa) fa = vecu(n);
    if CEXP (state & td_dep) dep = vecu(n);
    if CEXP (state & td_maxson) maxson = vecu(n, n);
    if CEXP (state & td_maxdfn) maxdfn = vecu(n);
    if CEXP (state & td_euler) euler = vecu(n);
    if CEXP (state & td_go) go = vvecu(n, vecu(21u, n));
    if CEXP (state & td_dis) dis = vec<weight_type>(n);

    u32 cnt = 0;
    dfs(
        tree, tree.root,
        [&](u32 u, u32 f) {
          if CEXP (state & td_dfn) dfn[u] = cnt;
          if CEXP (state & td_euler) euler[cnt] = u;
          if CEXP (state & (td_dfn | td_maxdfn | td_euler)) ++cnt;
          if CEXP (state & (td_sz | td_maxson)) sz[u] = 1;
          if CEXP (state & td_fa) fa[u] = f;
          if CEXP (state & td_go) {
            go[u][0] = f;
            for (u32 i = 1; i <= 20u && go[u][i - 1] < n; i++) go[u][i] = go[go[u][i - 1]][i - 1];
          }
        },
        [&](u32 to, u32 u, cT_(weight_type) w = 1) {
          if CEXP (state & td_dep) dep[to] = dep[u] + 1;
          if CEXP (state & td_dis) dis[to] = dis[u] + w;
        },
        [&](u32 to, u32 u, cT_(weight_type) = 1) {
          if CEXP (state & (td_sz | td_maxson)) sz[u] += sz[to];
          if CEXP (state & td_maxson)
            if (maxson[u] == n || sz[to] > sz[maxson[u]]) maxson[u] = to;
        },
        [&](u32 u, u32) {
          if CEXP (state & td_maxdfn) maxdfn[u] = cnt - 1;
        });
    return *this;
  }
};

}  // namespace tifa_libs::graph

#endif