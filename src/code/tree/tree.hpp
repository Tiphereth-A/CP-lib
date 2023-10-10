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
  void dfs_sz(size_t u, size_t fa) {
    sz[u] = 1;
    for (auto v : e[u])
      if (v != fa) {
        dfs_sz(v, u), sz[u] += sz[v];
        if(maxson[u] == e.size() || sz[v] > sz[maxson[u]]) maxson[u] = v;
      }
  }
  void dfs_top(size_t u, size_t _top) {
    top[u] = _top;
    if(maxson[u] == e.size()) return;
    dfs_top(maxson[u], _top);
    for(auto v: e[u]) if(top[v] != e.size()) dfs_top(v, _top); 
  }
  void dfs_maxson(size_t u, size_t fa) {
    sz[u] = 1;
    for (auto v : e[u])
      if (v != fa) dfs_maxson(v, u), sz[u] += sz[v];
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
  vec<size_t> getdfn() {
    dfn = vec<size_t>(e.size()), cnt = 0;
    dfs_dfn(root, e.size());
    return dfn;
  }
  vec<size_t> getsubsz() {
    sz = vec<size_t>(e.size());
    dfs_sz(root, e.size());
    return sz;
  }
  ptt<vec<size_t>> getmaxson() {
    sz = vec<size_t>(e.size());
    maxson = vec<size_t>(e.size(), e.size());
    dfs_maxson(root, e.size());
    return {sz, maxson};
  }
  vec<size_t> gettop() {
    assert(maxson.size());
    top = vec<size_t>(e.size(), e.size());
    dfs_top(root, root);
    return top;
  }
  vec<size_t> getfa() {
    f = vec<size_t>(e.size());
    dfs_fa(root, e.size());
    return f;
  }
  vec<size_t> getdep() {
    dep = vec<size_t>(e.size());
    dfs_dep(root, e.size());
    return dep;
  }
  explicit tree(vec<vec<size_t>> E, size_t ROOT = 0) : root(ROOT), e(E) {}
};
template <typename T>
class tree_w {
  vec<vec<std::pair<size_t, T>>> e;

 public:
};

}  // namespace tifa_libs::tree

#endif