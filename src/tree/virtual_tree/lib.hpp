#pragma once

#include "../../graph/ds/alist/lib.hpp"
#include "../ds/lib.hpp"
#include "../lca_hld/lib.hpp"

namespace tifa_libs {

template <tree_c G>
class virtual_tree {
  u32 root, tim;
  lca_hld<G> lca_;
  vecu st, used, vis;

  CEXP void touch(u32 x) NE {
    if (vis[x] == tim) return;
    vis[x] = tim, used.push_back(x);
  }
  CEXP void add_arc_(u32 u, u32 v) NE { vt.add_arc(u, v), touch(u), touch(v); }

  CEXP void insert(u32 x) NE {
    touch(x);
    u32 lca = lca_(x, st.back());
    if (lca == st.back()) return st.push_back(x);
    while (st.size() > 1 && lca_.info.dep[st[st.size() - 2]] >= lca_.info.dep[lca]) add_arc_(st[st.size() - 2], st.back()), st.pop_back();
    if (lca_.info.dep[st.back()] > lca_.info.dep[lca]) add_arc_(lca, st.back()), st.pop_back();
    if (st.back() != lca) touch(lca), st.push_back(lca);
    st.push_back(x);
  }

 public:
  using tree_info_t = lca_hld<G>::tree_info_t;
  tree<alist<>> vt;

  CEXPE virtual_tree(G CR tr) NE : root{tr.root}, tim{0}, lca_(tr), st{}, used{}, vis(tr.vsize()), vt(tr.vsize()) {}

  CEXP void build(vecu& a) NE {
    for (++tim; u32 x : used) vt[x].clear();
    used.clear(), st.clear();
    sort(a, [&](u32 a, u32 b) NE { return lca_.info.dfn[a] < lca_.info.dfn[b]; });
    for (st.push_back(root), touch(root); u32 x : a) insert(x);
    while (st.size() > 1) add_arc_(st[st.size() - 2], st.back()), st.pop_back();
    st.pop_back();
  }
};

}  // namespace tifa_libs
