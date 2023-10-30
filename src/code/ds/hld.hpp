#ifndef TIFA_LIBS_DS_HLD
#define TIFA_LIBS_DS_HLD

#include "../tree/tree.hpp"
#include "segtree.hpp"

namespace tifa_libs::ds {

// template <class T, T (*op)(T, T), T (*e)(), class F, T (*mapping)(F, T), F (*composition)(F, F), F (*id)()>
template <class T, auto op, auto e, class F = T, auto mapping = op, auto composition = e, auto id = e>
class hld {
  segtree<T, op, e, F, mapping, composition, id> t;

 public:
  graph::tree<void>& tr;

  explicit hld(graph::tree<void>& tr) : t(), tr(tr) {
    tr.template reset_dfs_info<graph::s_dep | graph::s_fa>();
    tr.template reset_top<true>();
  }
  explicit hld(graph::tree<void>& tr, const vec<T>& a) : t(), tr(tr) {
    tr.template reset_dfs_info<graph::s_dep | graph::s_fa>();
    tr.template reset_top<true>();
    vec<T> b(a.size());
    for(u32 i = 0; i < a.size(); ++ i) b[tr.dfn[i]] = a[i];
    build(b);
  }

  void build(const vec<T>& a) { t = segtree<T, op, e, F, mapping, composition, id>(a); }
  void chain_update(u32 u, u32 v, F f) {
    while (tr.top[u] != tr.top[v]) {
      if (tr.dep[tr.top[u]] < tr.dep[tr.top[v]]) std::swap(u, v);
      t.update(tr.dfn[tr.top[u]], tr.dfn[u], f), u = tr.fa[tr.top[u]];
    }
    if (tr.dfn[u] < tr.dfn[v]) std::swap(u, v);
    t.update(tr.dfn[v], tr.dfn[u], f);
  }
  void subtree_update(u32 u, F f) { t.update(tr.dfn[u], tr.dfn[u] + tr.sz[u] - 1, f); }
  void node_update(u32 u, F f) { t.update(tr.dfn[u], f); }
  void chain_set(u32 u, u32 v, T f) {
    while (tr.top[u] != tr.top[v]) {
      if (tr.dep[tr.top[u]] < tr.dep[tr.top[v]]) std::swap(u, v);
      t.set(tr.dfn[tr.top[u]], tr.dfn[u], f), u = tr.fa[tr.top[u]];
    }
    if (tr.dfn[u] < tr.dfn[v]) std::swap(u, v);
    t.set(tr.dfn[v], tr.dfn[u], f);
  }
  void subtree_set(u32 u, T f) { t.set(tr.dfn[u], tr.dfn[u] + tr.sz[u] - 1, f); }
  void node_set(u32 u, T f) { t.set(tr.dfn[u], f); }
  T chain_query(u32 u, u32 v) {
    T ret = e();
    while (tr.top[u] != tr.top[v]) {
      if (tr.dep[tr.top[u]] < tr.dep[tr.top[v]]) std::swap(u, v);
      ret = op(ret, t.query(tr.dfn[tr.top[u]], tr.dfn[u])), u = tr.fa[tr.top[u]];
    }
    if (tr.dfn[u] < tr.dfn[v]) std::swap(u, v);
    return op(ret, t.query(tr.dfn[v], tr.dfn[u]));
  }
  T subtree_query(u32 u) { return t.query(tr.dfn[u], tr.dfn[u] + tr.sz[u] - 1); }
  T node_query(u32 u) { return t.query(tr.dfn[u]); }
};

}  // namespace tifa_libs::ds

#endif