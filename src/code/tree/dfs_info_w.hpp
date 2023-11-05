#ifndef TIFA_LIBS_TREE_DFS_INFO_W
#define TIFA_LIBS_TREE_DFS_INFO_W

#include "../graph/dfs.hpp"
#include "treew.hpp"

namespace tifa_libs::graph {

enum dfs_info_w_state {
  dws_dfn = 1,
  dws_sz = 2,
  dws_fa = 4,
  dws_dep = 8,
  dws_maxson = 16,
  dws_go = 32,
  dws_dis = 64
};

template <class T>
struct tree_dfs_info_w {
  vec<u32> dfn, sz, fa, dep, maxson, top;
  vvec<u32> go;
  vec<T> dis;

  template <int state>
  tree_dfs_info_w& reset_dfs_info(treew<T> const& tree) {
    u32 n = (u32)tree.g.size();
    if constexpr (state & dws_dfn) dfn = vec<u32>(n);
    if constexpr (state & (dws_sz | dws_maxson)) sz = vec<u32>(n);
    if constexpr (state & dws_fa) fa = vec<u32>(n);
    if constexpr (state & dws_dep) dep = vec<u32>(n);
    if constexpr (state & dws_maxson) maxson = vec<u32>(n, n);
    if constexpr (state & dws_go) go = vec<vec<u32>>(n, vec<u32>(21u, n));
    if constexpr (state & dws_dis) dis = vec<T>(n);

    u32 cnt = 0;

    dfs(
        tree, tree.root,
        [&](u32 u, u32 f) {
          if constexpr (state & dws_dfn) dfn[u] = cnt++;
          if constexpr (state & (dws_sz | dws_maxson)) sz[u] = 1;
          if constexpr (state & dws_fa) fa[u] = f;
          if constexpr (state & dws_go) {
            go[u][0] = f;
            for (u32 i = 1; i <= 20u && go[u][i - 1] < n; i++) go[u][i] = go[go[u][i - 1]][i - 1];
          }
        },
        [&](u32 to, T const& w, u32 u) {
          if constexpr (state & dws_dep) dep[to] = dep[u] + 1;
          if constexpr (state & dws_dis) dis[to] = dis[u] + w;
        },
        [&](u32 to, T const&, u32 u) {
          if constexpr (state & (dws_sz | dws_maxson)) sz[u] += sz[to];
          if constexpr (state & dws_maxson)
            if (maxson[u] == n || sz[to] > sz[maxson[u]]) maxson[u] = to;
        });
    return *this;
  }

  template <bool need_dfn = false>
  tree_dfs_info_w& reset_top(treew<T> const& tree) {
    u32 n = (u32)tree.g.size();
    if (maxson.empty()) reset_dfs_info<dws_maxson>(tree);
    if constexpr (need_dfn) dfn = vec<u32>(n);
    top = vec<u32>(n, n);

    u32 cnt = 0;
    dfs_top_(tree, tree.root, tree.root, [&](u32 u, u32 top_) {
      if constexpr (need_dfn) dfn[u] = cnt++;
      top[u] = top_;
    });
    return *this;
  }

 private:
  template <class F>
  void dfs_top_(treew<T> const& tree, u32 u, u32 top_, F&& f) {
    f(u, top_);
    if (maxson[u] == tree.g.size()) return;
    dfs_top_(tree, maxson[u], top_, std::forward<F>(f));
    for (u32 to : tree.g[u])
      if (top[to] == tree.g.size()) dfs_top_(tree, to, to, std::forward<F>(f));
  }
};

}  // namespace tifa_libs::graph

#endif