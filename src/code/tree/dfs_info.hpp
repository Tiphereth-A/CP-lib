#ifndef TIFALIBS_TREE_DFS_INFO
#define TIFALIBS_TREE_DFS_INFO

#include "../graph/dfs.hpp"
#include "tree.hpp"

namespace tifa_libs::graph {

enum dfs_info_state {
  s_dfn = 1,
  s_sz = 2,
  s_fa = 4,
  s_dep = 8,
  s_maxson = 16,
  s_go = 32
};

struct tree_dfs_info {
  vec<u32> dfn, sz, fa, dep, maxson, top;
  vvec<u32> go;

  template <int state>
  tree_dfs_info& reset_dfs_info(tree const& tree) {
    u32 n = (u32)tree.g.size();
    if constexpr (state & s_dfn) dfn = vec<u32>(n);
    if constexpr (state & (s_sz | s_maxson)) sz = vec<u32>(n);
    if constexpr (state & s_fa) fa = vec<u32>(n);
    if constexpr (state & s_dep) dep = vec<u32>(n);
    if constexpr (state & s_maxson) maxson = vec<u32>(n, n);
    if constexpr (state & s_go) go = vec<vec<u32>>(n, vec<u32>(21u, n));

    u32 cnt = 0;

    dfs(
        tree, tree.root,
        [&](u32 u, u32 f) {
          if constexpr (state & s_dfn) dfn[u] = cnt++;
          if constexpr (state & (s_sz | s_maxson)) sz[u] = 1;
          if constexpr (state & s_fa) fa[u] = f;
          if constexpr (state & s_go) {
            go[u][0] = f;
            for (u32 i = 1; i <= 20u && go[u][i - 1] < n; i++) go[u][i] = go[go[u][i - 1]][i - 1];
          }
        },
        [&](u32 to, u32 u) {
          if constexpr (state & s_dep) dep[to] = dep[u] + 1;
        },
        [&](u32 to, u32 u) {
          if constexpr (state & (s_sz | s_maxson)) sz[u] += sz[to];
          if constexpr (state & s_maxson)
            if (maxson[u] == n || sz[to] > sz[maxson[u]]) maxson[u] = to;
        });
    return *this;
  }

  template <bool need_dfn = false>
  tree_dfs_info& reset_top(tree const& tree) {
    u32 n = (u32)tree.g.size();
    if (maxson.empty()) reset_dfs_info<s_maxson>(tree);
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
  void dfs_top_(tree const& tree, u32 u, u32 top_, F&& f) {
    f(u, top_);
    if (maxson[u] == tree.g.size()) return;
    dfs_top_(tree, maxson[u], top_, std::forward<F>(f));
    for (u32 to : tree.g[u])
      if (top[to] == tree.g.size()) dfs_top_(tree, to, to, std::forward<F>(f));
  }
};

}  // namespace tifa_libs::graph

#endif