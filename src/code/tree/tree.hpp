#ifndef TIFA_LIBS_TREE_TREE
#define TIFA_LIBS_TREE_TREE

#include "../graph/adjlist.hpp"

namespace tifa_libs::graph {

enum state_tdfs {
  s_dfn = 1,
  s_sz = 2,
  s_fa = 4,
  s_dep = 8,
  s_maxson = 16
};

template <class T = void>
struct tree : public adjlist<T> {
  u32 rt;
  vec<u32> dfn, sz, fa, dep, maxson, top;

  explicit tree(u32 n, u32 root = 0) : adjlist<T>(n), rt(root) {}

  void clear(u32 u = 0, u32 fa = 0) {
    for (auto v : this->g[u])
      if (v.to != fa) clear(v.to, u);
    this->g[u].clear();
  }

  template <int state>
  inline void reset_dfs_info() {
    u32 n = (u32)this->v_size();
    if constexpr (state & s_dfn) dfn = vec<u32>(n);
    if constexpr (state & (s_sz | s_maxson)) sz = vec<u32>(n);
    if constexpr (state & s_fa) fa = vec<u32>(n);
    if constexpr (state & s_dep) dep = vec<u32>(n);
    if constexpr (state & s_maxson) maxson = vec<u32>(n, n);

    u32 cnt = 0;
    auto before = [&](u32 u, u32 f) {
      if constexpr (state & s_dfn) dfn[u] = cnt++;
      if constexpr (state & (s_sz | s_maxson)) sz[u] = 1;
      if constexpr (state & s_fa) fa[u] = f;
    };
    auto pre_dfs = [&](auto const& ev, u32 u) {
      if constexpr (state & s_dep) dep[ev.to] = dep[u] + 1;
    };
    auto post_dfs = [&](auto const& ev, u32 u) {
      if constexpr (state & (s_sz | s_maxson)) sz[u] += sz[ev.to];
      if constexpr (state & s_maxson)
        if (maxson[u] == n || sz[ev.to] > sz[maxson[u]]) maxson[u] = ev.to;
    };

    dfs_(rt, n, before, pre_dfs, post_dfs);
  }

  template <bool need_dfn = false>
  void reset_top() {
    u32 n = (u32)this->v_size();
    if (maxson.empty()) reset_dfs_info<s_maxson>();
    if constexpr (need_dfn) dfn = vec<u32>(n);
    top = vec<u32>(n, n);

    u32 cnt = 0;
    auto before = [&](u32 u, u32 top_) {
      if constexpr (need_dfn) dfn[u] = cnt++;
      top[u] = top_;
    };
    dfs_top_(rt, rt, before);
  }

 private:
  template <class Fb, class Fp, class Fs>
  void dfs_(u32 u, u32 fa, Fb before, Fp pre_dfs, Fs post_dfs) {
    before(u, fa);
    for (auto v : this->g[u])
      if (v.to != fa) {
        pre_dfs(v, u);
        dfs_(v.to, u, before, pre_dfs, post_dfs);
        post_dfs(v, u);
      }
  }

  template <class F>
  void dfs_top_(u32 u, u32 top_, F before) {
    before(u, top_);
    if (maxson[u] == this->v_size()) return;
    dfs_top_(maxson[u], top_, before);
    for (auto v : this->g[u])
      if (top[v.to] == this->v_size()) dfs_top_(v.to, v.to, before);
  }
};

}  // namespace tifa_libs::graph

#endif