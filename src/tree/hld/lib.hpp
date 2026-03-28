#pragma once

#include "../../ds/segtree/hp/lib.hpp"
#include "../dfs/info/lib.hpp"
#include "../dfs/top/lib.hpp"
#include "../ds/lib.hpp"

namespace tifa_libs {
namespace hld_impl_ {
template <bool enable_tag, tree_c tree_t, class T, auto op, class F, auto mapping, auto composition>
class hld {
  segtree_impl_::segtree<enable_tag, T, op, F, mapping, composition> t;

 public:
  using tree_info_t = tree_dfs_info<tree_t, tdi_dfn, tdi_maxson, tdi_dep, tdi_fa>;

  tree_t CR tr;
  tree_info_t info;
  vecu top;

  CEXP hld(cT_(T) e, cT_(F) id, tree_t CR tr, tree_info_t CR info_) NE : t(e, id), tr(tr), info{info_}, top(tree_top<tree_t, true>(tr, info.dfn, info.maxson)) {}
  CEXP hld(cT_(T) e, cT_(F) id, tree_t CR tr) NE : hld(e, id, tr, tree_info_t(tr)) {}
  CEXP hld(cT_(T) e, cT_(F) id, tree_t CR tr, tree_info_t CR info_, spn<T> a) NE : hld(e, id, tr, info_) {
    vec<T> b(a.size());
    flt_ (u32, i, 0, (u32)a.size()) b[info.dfn[i]] = a[i];
    build(b);
  }
  CEXP hld(tree_t CR tr, spn<T> a) NE : hld(tr, tree_info_t(tr), a) {}

  CEXP void build(spn<T> a) NE { t.reset(a); }
  CEXP void chain_update(u32 u, u32 v, cT_(F) f) NE {
    while (top[u] != top[v]) {
      if (info.dep[top[u]] < info.dep[top[v]]) swap(u, v);
      t.update(info.dfn[top[u]], info.dfn[u] + 1, f);
      u = info.fa[top[u]];
    }
    if (info.dfn[u] < info.dfn[v]) swap(u, v);
    t.update(info.dfn[v], info.dfn[u] + 1, f);
  }
  CEXP void subtree_update(u32 u, cT_(F) f) NE { t.update(info.dfn[u], info.dfn[u] + info.sz[u], f); }
  CEXP void node_update(u32 u, cT_(F) f) NE { t.update(info.dfn[u], f); }
  CEXP void chain_set(u32 u, u32 v, cT_(T) f) NE {
    while (top[u] != top[v]) {
      if (info.dep[top[u]] < info.dep[top[v]]) swap(u, v);
      t.set(info.dfn[top[u]], info.dfn[u] + 1, f), u = info.fa[top[u]];
    }
    if (info.dfn[u] < info.dfn[v]) swap(u, v);
    t.set(info.dfn[v], info.dfn[u] + 1, f);
  }
  CEXP void subtree_set(u32 u, cT_(T) f) NE { t.set(info.dfn[u], info.dfn[u] + info.sz[u], f); }
  CEXP void node_set(u32 u, cT_(T) f) NE { t.set(info.dfn[u] + 1, f); }
  CEXP T chain_query(u32 u, u32 v) NE {
    T ret = t.E;
    while (top[u] != top[v]) {
      if (info.dep[top[u]] < info.dep[top[v]]) swap(u, v);
      ret = op(ret, t.query(info.dfn[top[u]], info.dfn[u] + 1)), u = info.fa[top[u]];
    }
    if (info.dfn[u] < info.dfn[v]) swap(u, v);
    return op(ret, t.query(info.dfn[v], info.dfn[u] + 1));
  }
  CEXP T subtree_query(u32 u) NE { return t.query(info.dfn[u], info.dfn[u] + info.sz[u]); }
  CEXP T node_query(u32 u) NE { return t.query(info.dfn[u]); }
};
}  // namespace hld_impl_

template <tree_c tree_t, class T, auto op, class F, auto mapping, auto composition>
using hld = hld_impl_::hld<true, tree_t, T, op, F, mapping, composition>;
template <tree_c tree_t, class T, auto op, auto mapping>
class hld_notag : public hld_impl_::hld<false, tree_t, T, op, T, mapping, mapping> {
  using base = hld_impl_::hld<false, tree_t, T, op, T, mapping, mapping>;

 public:
  CEXP hld_notag(cT_(T) e, tree_t CR tr, base::tree_info_t CR info) NE : base(e, e, tr, info) {}
  template <class V>
  CEXP hld_notag(cT_(T) e, tree_t CR tr) NE : base(e, e, tr) {}
  CEXP hld_notag(cT_(T) e, tree_t CR tr, base::tree_info_t CR info, spn<T> a) NE : base(e, e, tr, info, a) {}
};

}  // namespace tifa_libs
