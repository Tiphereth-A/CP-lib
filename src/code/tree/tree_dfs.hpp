#ifndef TIFA_LIBS_TREE_TREE_DFS
#define TIFA_LIBS_TREE_TREE_DFS

#include "tree.hpp"

namespace tifa_libs::graph {

namespace dfs_impl_ {

template <class T, class Fb, class Fp, class Fs>
void dfs_(tree<T> const& tr, u32 u, u32 fa, Fb before, Fp pre_dfs, Fs post_dfs) {
  before(u, fa);
  for (auto v : tr[u])
    if (v.to != fa) {
      pre_dfs(v, u);
      dfs_(tr, v.to, u, before, pre_dfs, post_dfs);
      post_dfs(v, u);
    }
}

template <class T>
void dfs_top_(tree<T> const& tr, u32 u, u32 top_, vec<u32>& res, vec<u32> const& mson) {
  res[u] = top_;
  if (mson[u] == tr.v_size()) return;
  dfs_top_(tr, mson[u], top_, res, mson);
  for (auto [v] : tr[u])
    if (res[v] == tr.v_size()) dfs_top_(tr, v, v, res, mson);
}

}  // namespace dfs_impl_

enum dfs_state {
  dfn = 1,
  sz = 2,
  fa = 4,
  dep = 8,
  maxson = 16
};

template <class T, int state = dfn | sz | fa | dep | maxson>
inline void tree_dfs(tree<T> const& tr, vec<u32>& dfn, vec<u32>& sz, vec<u32>& fa, vec<u32>& dep, vec<u32>& maxson) {
  u32 n = (u32)tr.v_size();
  if constexpr (state & dfs_state::dfn) dfn.resize(n);
  if constexpr (state & (dfs_state::sz | dfs_state::maxson)) sz.resize(n);
  if constexpr (state & dfs_state::fa) fa.resize(n);
  if constexpr (state & dfs_state::dep) dep.resize(n);
  if constexpr (state & dfs_state::maxson) maxson.resize(n, n);

  u32 cnt = 0;
  auto before = [&](u32 u, u32 f) {
    if constexpr (state & dfs_state::dfn) dfn[u] = cnt++;
    if constexpr (state & (dfs_state::sz | dfs_state::maxson)) sz[u] = 1;
    if constexpr (state & dfs_state::fa) fa[u] = f;
  };
  auto pre_dfs = [&](auto const& ev, u32 u) {
    if constexpr (state & dfs_state::dep) dep[ev.to] = dep[u] + 1;
  };
  auto post_dfs = [&](auto const& ev, u32 u) {
    if constexpr (state & (dfs_state::sz | dfs_state::maxson)) sz[u] += sz[ev.to];
    if constexpr (state & dfs_state::maxson)
      if (maxson[u] == n || sz[ev.to] > sz[maxson[u]]) maxson[u] = ev.to;
  };

  dfs_impl_::dfs_(tr, tr.root(), n, before, pre_dfs, post_dfs);
}

template <class T>
void tree_dfs_top(tree<T> const& tr, vec<u32> const& maxson, vec<u32>& top) {
  u32 n = (u32)tr.v_size();
  assert(maxson.size() == n);
  top.resize(n, n);
  dfs_impl_::dfs_top_(tr, tr.root(), tr.root(), top, maxson);
}

}  // namespace tifa_libs::graph

#endif