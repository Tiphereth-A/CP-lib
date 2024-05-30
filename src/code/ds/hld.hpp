#ifndef TIFALIBS_DS_HLD
#define TIFALIBS_DS_HLD

#include "../tree/tree.hpp"
#include "../tree/tree_top.hpp"
#include "segtree.hpp"

namespace tifa_libs::ds {

template <class T, auto op, auto e, class F = T, auto mapping = op, auto composition = e, auto id = e>
class hld {
  segtree<T, op, e, F, mapping, composition, id> t;

 public:
  graph::tree& tr;
  graph::tree_dfs_info<graph::tree> info;
  vecu top;

  explicit CEXP hld(graph::tree& tr) : t(), tr(tr), info() {
    info.template reset_dfs_info<graph::td_dep | graph::td_fa>(tr);
    top = graph::tree_top<graph::tree, true>(tr, info);
  }
  explicit CEXP hld(graph::tree& tr, vec<T> CR a) : hld(tr) {
    vec<T> b(a.size());
    flt_ (u32, i, 0, (u32)a.size()) b[info.dfn[i]] = a[i];
    build(b);
  }

  CEXP void build(vec<T> CR a) { t.reset(a); }
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