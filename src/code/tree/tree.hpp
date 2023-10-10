#ifndef TIFA_LIBS_DS_TREE
#define TIFA_LIBS_DS_TREE

#include "../util/util.hpp"

namespace tifa_libs::tree {

class tree {
  size_t root;
  vec<vec<size_t>> e;
  vec<size_t> dfn, sz, f, dep, maxson, top;
  size_t cnt;
  void dfs_dfn(size_t u, size_t fa) {
    dfn[u] = cnt++;
    for (auto v : e[u])
      if (v != fa) dfs_dfn(v, u);
  }
  void dfs_maxson(size_t u, size_t fa) {
    sz[u] = 1;
    for (auto v : e[u])
      if (v != fa) {
        dfs_maxson(v, u), sz[u] += sz[v];
        if (maxson[u] == e.size() || sz[v] > sz[maxson[u]]) maxson[u] = v;
      }
  }
  void dfs_top(size_t u, size_t _top) {
    top[u] = _top, dfn[u] = cnt++;
    if (maxson[u] == e.size()) return;
    dfs_top(maxson[u], _top);
    for (auto v : e[u])
      if (top[v] == e.size()) dfs_top(v, v);
  }
  void dfs_sz(size_t u, size_t fa) {
    sz[u] = 1;
    for (auto v : e[u])
      if (v != fa) dfs_sz(v, u), sz[u] += sz[v];
  }
  void dfs_fa(size_t u, size_t fa) {
    f[u] = fa;
    for (auto v : e[u])
      if (v != fa) dfs_fa(v, u);
  }
  void dfs_dep(size_t u, size_t fa) {
    for (auto v : e[u])
      if (v != fa) dep[v] = dep[u] + 1, dfs_dep(v, u);
  }

 public:
  explicit tree(vec<vec<size_t>> E, size_t ROOT = 0) : root(ROOT), e(E) {}
  explicit tree(size_t N, size_t ROOT = 0) : root(ROOT), e(N) {}
  void add(size_t u, size_t v) { e[u].push_back(v), e[v].push_back(u); }
  vec<size_t> get_dfn() {  // dfn
    dfn = vec<size_t>(e.size()), cnt = 0;
    dfs_dfn(root, e.size());
    return dfn;
  }
  vec<size_t> get_sz() {  // sz
    sz = vec<size_t>(e.size());
    dfs_sz(root, e.size());
    return sz;
  }
  ptt<vec<size_t>> get_sz_maxson() {  // sz maxson
    sz = vec<size_t>(e.size());
    maxson = vec<size_t>(e.size(), e.size());
    dfs_maxson(root, e.size());
    return {sz, maxson};
  }
  ptt<vec<size_t>> get_top_dfn() {  // top dfn
    assert(maxson.size());
    top = vec<size_t>(e.size(), e.size());
    dfn = vec<size_t>(e.size()), cnt = 0;
    dfs_top(root, root);
    return {top, dfn};
  }
  vec<size_t> get_fa() {
    f = vec<size_t>(e.size());
    dfs_fa(root, e.size());
    return f;
  }
  vec<size_t> get_dep() {
    dep = vec<size_t>(e.size());
    dfs_dep(root, e.size());
    return dep;
  }
  size_t lca(size_t u, size_t v) {
    if (!dep.size()) get_dep();
    if (!f.size()) get_fa();
    if (!maxson.size()) get_sz_maxson();
    if (!top.size()) get_top_dfn();
    while (top[u] != top[v]) dep[top[u]] < dep[top[v]] ? v = f[top[v]] : u = f[top[u]];
    return dep[u] > dep[v] ? v : u;
  }
};
template <typename T>
class tree_w {
  vec<vec<std::pair<size_t, T>>> e;

 public:
};

}  // namespace tifa_libs::tree

#endif