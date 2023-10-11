#ifndef TIFA_LIBS_DS_HEAVY_CHAIN_SUBDIVISION
#define TIFA_LIBS_DS_HEAVY_CHAIN_SUBDIVISION

#include "../ds/segtree.hpp"
#include "../tree/tree.hpp"
#include "../util/util.hpp"

namespace tifa_libs::ds {

// template <class T, T (*op)(T, T), T (*e)(), class F, T (*mapping)(F, T), F (*composition)(F, F), F (*id)()>
template <class T, auto op, auto e, class F, auto mapping, auto composition, auto id>
class heavy_chain_s : public tree::tree {
  segtree<T, op, e, F, mapping, composition, id> t;

 public:
  explicit constexpr heavy_chain_s(size_t N = 0, size_t ROOT = 0) : tree(N, ROOT) {}
  void build(const vec<T>& a) { t = segtree<T, op, e, F, mapping, composition, id>(a); }
  void chain_update(size_t u, size_t v, F f) {
    assert(dep.size() && f.size() && maxson.size() && top.size());
    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
      t.update(dfn[top[u]], dfn[u], f), u = f[top[u]];
    }
    if (dfn[u] < dfn[v]) std::swap(u, v);
    t.update(dfn[v], dfn[u], f);
  }
  void subtree_update(size_t u, F f) {
    assert(sz.size() && dfn.size());
    t.update(dfn[u], dfn[u] + sz[u] - 1, f);
  }
  void node_update(size_t u, F f) {
    t.update(dfn[u], f);
  }
  T chain_query(size_t u, size_t v) {
    assert(dep.size() && f.size() && maxson.size() && top.size());
    T ret = e();
    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
      ret = op(ret, t.query(dfn[top[u]], dfn[u])), u = f[top[u]];
    }
    if (dfn[u] < dfn[v]) std::swap(u, v);
    return op(ret, t.query(dfn[v], dfn[u]));
  }
  T subtree_query(size_t u) {
    assert(sz.size() && dfn.size());
    return t.query(dfn[u], dfn[u] + sz[u] - 1);
  }
  T node_query(size_t u) {
    return t.query(dfn[u]);
  }
};

}  // namespace tifa_libs::ds

#endif