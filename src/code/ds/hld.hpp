#ifndef TIFALIBS_DS_HLD
#define TIFALIBS_DS_HLD

#include "../tree/tree.hpp"
#include "../tree/tree_top.hpp"
#include "segtree.hpp"

namespace tifa_libs::ds {

template <class T, auto op, auto e, class F = T, auto mapping = op, auto composition = e, auto id = e>
requires requires(T val, T val_l, T val_r, F tag, F tag_l, F tag_r) {
  { e() } -> std::same_as<T>;
  { id() } -> std::same_as<F>;
  { op(val_l, val_r) } -> std::same_as<T>;
  { mapping(tag, val) } -> std::same_as<T>;
  { composition(tag_l, tag_r) } -> std::same_as<F>;
}
class hld {
  segtree<T, op, e, F, mapping, composition, id> t;

 public:
  graph::tree& tr;
  graph::tree_dfs_info<graph::tree> info;
  vecu top;

  explicit constexpr hld(graph::tree& tr) : t(), tr(tr), info() {
    info.template reset_dfs_info<graph::td_dep | graph::td_fa>(tr);
    top = graph::tree_top<graph::tree, true>(tr, info);
  }
  explicit constexpr hld(graph::tree& tr, vec<T> const& a) : hld(tr) {
    vec<T> b(a.size());
    for (u32 i = 0; i < a.size(); ++i) b[info.dfn[i]] = a[i];
    build(b);
  }

  constexpr void build(vec<T> const& a) { t = segtree<T, op, e, F, mapping, composition, id>(a); }
  constexpr void chain_update(u32 u, u32 v, F f) {
    while (top[u] != top[v]) {
      if (info.dep[top[u]] < info.dep[top[v]]) std::swap(u, v);
      t.update(info.dfn[top[u]], info.dfn[u], f), u = info.fa[top[u]];
    }
    if (info.dfn[u] < info.dfn[v]) std::swap(u, v);
    t.update(info.dfn[v], info.dfn[u], f);
  }
  constexpr void subtree_update(u32 u, F f) { t.update(info.dfn[u], info.dfn[u] + info.sz[u] - 1, f); }
  constexpr void node_update(u32 u, F f) { t.update(info.dfn[u], f); }
  constexpr void chain_set(u32 u, u32 v, T f) {
    while (top[u] != top[v]) {
      if (info.dep[top[u]] < info.dep[top[v]]) std::swap(u, v);
      t.set(info.dfn[top[u]], info.dfn[u], f), u = info.fa[top[u]];
    }
    if (info.dfn[u] < info.dfn[v]) std::swap(u, v);
    t.set(info.dfn[v], info.dfn[u], f);
  }
  constexpr void subtree_set(u32 u, T f) { t.set(info.dfn[u], info.dfn[u] + info.sz[u] - 1, f); }
  constexpr void node_set(u32 u, T f) { t.set(info.dfn[u], f); }
  constexpr T chain_query(u32 u, u32 v) {
    T ret = e();
    while (top[u] != top[v]) {
      if (info.dep[top[u]] < info.dep[top[v]]) std::swap(u, v);
      ret = op(ret, t.query(info.dfn[top[u]], info.dfn[u])), u = info.fa[top[u]];
    }
    if (info.dfn[u] < info.dfn[v]) std::swap(u, v);
    return op(ret, t.query(info.dfn[v], info.dfn[u]));
  }
  constexpr T subtree_query(u32 u) { return t.query(info.dfn[u], info.dfn[u] + info.sz[u] - 1); }
  constexpr T node_query(u32 u) { return t.query(info.dfn[u]); }
};

}  // namespace tifa_libs::ds

#endif