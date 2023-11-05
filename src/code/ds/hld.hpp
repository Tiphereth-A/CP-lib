#ifndef TIFA_LIBS_DS_HLD
#define TIFA_LIBS_DS_HLD

#include "../tree/dfs_info.hpp"
#include "segtree.hpp"

namespace tifa_libs::ds {

// template <class T, T (*op)(T, T), T (*e)(), class F, T (*mapping)(F, T), F (*composition)(F, F), F (*id)()>
template <class T, auto op, auto e, class F = T, auto mapping = op, auto composition = e, auto id = e>
class hld {
  segtree<T, op, e, F, mapping, composition, id> t;

 public:
  graph::tree& tr;
  graph::tree_dfs_info info;

  explicit hld(graph::tree& tr) : t(), tr(tr) { info.reset_dfs_info<graph::s_dep | graph::s_fa>(tr).reset_top<true>(tr); }
  explicit hld(graph::tree& tr, const vec<T>& a) : hld(tr) {
    vec<T> b(a.size());
    for (u32 i = 0; i < a.size(); ++i) b[info.dfn[i]] = a[i];
    build(b);
  }

  void build(const vec<T>& a) { t = segtree<T, op, e, F, mapping, composition, id>(a); }
  void chain_update(u32 u, u32 v, F f) {
    while (info.top[u] != info.top[v]) {
      if (info.dep[info.top[u]] < info.dep[info.top[v]]) std::swap(u, v);
      t.update(info.dfn[info.top[u]], info.dfn[u], f), u = info.fa[info.top[u]];
    }
    if (info.dfn[u] < info.dfn[v]) std::swap(u, v);
    t.update(info.dfn[v], info.dfn[u], f);
  }
  void subtree_update(u32 u, F f) { t.update(info.dfn[u], info.dfn[u] + info.sz[u] - 1, f); }
  void node_update(u32 u, F f) { t.update(info.dfn[u], f); }
  void chain_set(u32 u, u32 v, T f) {
    while (info.top[u] != info.top[v]) {
      if (info.dep[info.top[u]] < info.dep[info.top[v]]) std::swap(u, v);
      t.set(info.dfn[info.top[u]], info.dfn[u], f), u = info.fa[info.top[u]];
    }
    if (info.dfn[u] < info.dfn[v]) std::swap(u, v);
    t.set(info.dfn[v], info.dfn[u], f);
  }
  void subtree_set(u32 u, T f) { t.set(info.dfn[u], info.dfn[u] + info.sz[u] - 1, f); }
  void node_set(u32 u, T f) { t.set(info.dfn[u], f); }
  T chain_query(u32 u, u32 v) {
    T ret = e();
    while (info.top[u] != info.top[v]) {
      if (info.dep[info.top[u]] < info.dep[info.top[v]]) std::swap(u, v);
      ret = op(ret, t.query(info.dfn[info.top[u]], info.dfn[u])), u = info.fa[info.top[u]];
    }
    if (info.dfn[u] < info.dfn[v]) std::swap(u, v);
    return op(ret, t.query(info.dfn[v], info.dfn[u]));
  }
  T subtree_query(u32 u) { return t.query(info.dfn[u], info.dfn[u] + info.sz[u] - 1); }
  T node_query(u32 u) { return t.query(info.dfn[u]); }
};

}  // namespace tifa_libs::ds

#endif