#ifndef TIFA_LIBS_DS_TREE
#define TIFA_LIBS_DS_TREE

#include "../util/util.hpp"

namespace tifa_libs::tree {

class tree {
  vec<vec<usz>> e_;
  usz cnt;

  void dfs_dfn(usz u, usz fa) {
    dfn[u] = cnt++;
    for (auto v : e_[u])
      if (v != fa) dfs_dfn(v, u);
  }
  void dfs_maxson(usz u, usz fa) {
    sz[u] = 1;
    for (auto v : e_[u])
      if (v != fa) {
        dfs_maxson(v, u), sz[u] += sz[v];
        if (maxson[u] == e_.size() || sz[v] > sz[maxson[u]]) maxson[u] = v;
      }
  }
  void dfs_top(usz u, usz _top) {
    top[u] = _top, dfn[u] = cnt++;
    if (maxson[u] == e_.size()) return;
    dfs_top(maxson[u], _top);
    for (auto v : e_[u])
      if (top[v] == e_.size()) dfs_top(v, v);
  }
  void dfs_sz(usz u, usz fa) {
    sz[u] = 1;
    for (auto v : e_[u])
      if (v != fa) dfs_sz(v, u), sz[u] += sz[v];
  }
  void dfs_fa(usz u, usz fa) {
    f[u] = fa;
    for (auto v : e_[u])
      if (v != fa) dfs_fa(v, u);
  }
  void dfs_dep(usz u, usz fa) {
    for (auto v : e_[u])
      if (v != fa) dep[v] = dep[u] + 1, dfs_dep(v, u);
  }

 public:
  usz root;
  vec<usz> dfn, sz, f, dep, maxson, top;

  explicit tree(usz N = 0, usz ROOT = 0) : e_(N), root(ROOT) {}

  void s_req() {
    if (!dep.size()) get_dep();
    if (!f.size()) get_fa();
    if (!maxson.size()) get_sz_maxson();
    if (!top.size()) get_top_dfn();
  }
  void subt_req() {
    if (!sz.size()) get_sz();
    if (!dfn.size()) get_dfn();
  }
  void add(usz u, usz v) { e_[u].push_back(v), e_[v].push_back(u); }
  vec<usz> get_dfn() {  // dfn
    dfn = vec<usz>(e_.size()), cnt = 0;
    dfs_dfn(root, e_.size());
    return dfn;
  }
  vec<usz> get_sz() {  // sz
    sz = vec<usz>(e_.size());
    dfs_sz(root, e_.size());
    return sz;
  }
  ptt<vec<usz>> get_sz_maxson() {  // sz maxson
    sz = vec<usz>(e_.size());
    maxson = vec<usz>(e_.size(), e_.size());
    dfs_maxson(root, e_.size());
    return {sz, maxson};
  }
  ptt<vec<usz>> get_top_dfn() {  // top dfn
    assert(maxson.size());
    top = vec<usz>(e_.size(), e_.size());
    dfn = vec<usz>(e_.size()), cnt = 0;
    dfs_top(root, root);
    return {top, dfn};
  }
  vec<usz> get_fa() {
    f = vec<usz>(e_.size());
    dfs_fa(root, e_.size());
    return f;
  }
  vec<usz> get_dep() {
    dep = vec<usz>(e_.size());
    dfs_dep(root, e_.size());
    return dep;
  }
  usz lca(usz u, usz v) {
    s_req();
    while (top[u] != top[v]) dep[top[u]] < dep[top[v]] ? v = f[top[v]] : u = f[top[u]];
    return dep[u] > dep[v] ? v : u;
  }
};
template <typename T>
class tree_w {
  vec<vec<std::pair<usz, T>>> e_;

 public:
};

}  // namespace tifa_libs::tree

#endif