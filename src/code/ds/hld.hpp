#ifndef TIFALIBS_DS_HLD
#define TIFALIBS_DS_HLD

#include "../tree/dfs_info.hpp"
#include "../tree/tree.hpp"
#include "../tree/tree_top.hpp"
#include "segtree.hpp"

namespace tifa_libs::ds {

template <class T, auto op, auto e, class F = T, auto mapping = op, auto composition = e, auto id = e>
class hld {
  segtree<T, op, e, F, mapping, composition, id> t;

 public:
  using tree_info_t = graph::tree_dfs_info<graph::tree, graph::td_dfn_tag, graph::td_maxson_tag, graph::td_dep_tag, graph::td_fa_tag>;

  graph::tree CR tr;
  tree_info_t info;
  vecu top;

  CEXP hld(graph::tree CR tr, tree_info_t CR info_) : t(), tr(tr), info{info_} { top = graph::tree_top<graph::tree, true>(tr, info.dfn, info.maxson); }
  CEXPE hld(graph::tree CR tr) : hld(tr, tree_info_t(tr)) {}
  CEXP hld(graph::tree CR tr, tree_info_t CR info_, spn<T> a) : hld(tr, info_) {
    vec<T> b(a.size());
    flt_ (u32, i, 0, (u32)a.size()) b[info.dfn[i]] = a[i];
    build(b);
  }
  CEXP hld(graph::tree CR tr, spn<T> a) : hld(tr, tree_info_t(tr), a) {}

  CEXP void build(spn<T> a) { t.reset(a); }
  CEXP void chain_update(u32 u, u32 v, cT_(F) f) {
    while (top[u] != top[v]) {
      if (info.dep[top[u]] < info.dep[top[v]]) swap(u, v);
      t.update(info.dfn[top[u]], info.dfn[u] + 1, f), u = info.fa[top[u]];
    }
    if (info.dfn[u] < info.dfn[v]) swap(u, v);
    t.update(info.dfn[v], info.dfn[u] + 1, f);
  }
  CEXP void subtree_update(u32 u, cT_(F) f) { t.update(info.dfn[u], info.dfn[u] + info.sz[u], f); }
  CEXP void node_update(u32 u, cT_(F) f) { t.update(info.dfn[u], f); }
  CEXP void chain_set(u32 u, u32 v, cT_(T) f) {
    while (top[u] != top[v]) {
      if (info.dep[top[u]] < info.dep[top[v]]) swap(u, v);
      t.set(info.dfn[top[u]], info.dfn[u] + 1, f), u = info.fa[top[u]];
    }
    if (info.dfn[u] < info.dfn[v]) swap(u, v);
    t.set(info.dfn[v], info.dfn[u] + 1, f);
  }
  CEXP void subtree_set(u32 u, cT_(T) f) { t.set(info.dfn[u], info.dfn[u] + info.sz[u], f); }
  CEXP void node_set(u32 u, cT_(T) f) { t.set(info.dfn[u] + 1, f); }
  CEXP T chain_query(u32 u, u32 v) {
    T ret = e();
    while (top[u] != top[v]) {
      if (info.dep[top[u]] < info.dep[top[v]]) swap(u, v);
      ret = op(ret, t.query(info.dfn[top[u]], info.dfn[u] + 1)), u = info.fa[top[u]];
    }
    if (info.dfn[u] < info.dfn[v]) swap(u, v);
    return op(ret, t.query(info.dfn[v], info.dfn[u] + 1));
  }
  CEXP T subtree_query(u32 u) { return t.query(info.dfn[u], info.dfn[u] + info.sz[u]); }
  CEXP T node_query(u32 u) { return t.query(info.dfn[u]); }
};

}  // namespace tifa_libs::ds

#endif