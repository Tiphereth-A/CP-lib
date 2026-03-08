#pragma once

#include "../ds/lib.hpp"
#include "../lca_hld/lib.hpp"

namespace tifa_libs::graph {

template <tree_c G>
class virtual_tree {
  G CR tr;
  lca_hld<G> lca_;
  vecu st;

  CEXP void insert(u32 x) NE {
    u32 lca = lca_(x, st.back());
    if (lca == st.back()) return st.push_back(x);
    while (st.size() > 1 && lca_.info.dep[st[st.size() - 2]] >= lca_.info.dep[lca]) {
      if CEXP (alistw_c<G>) vt.add_arc(st[st.size() - 2], st.back(), {});
      else vt.add_arc(st[st.size() - 2], st.back());
      st.pop_back();
    }
    if (lca_.info.dep[st.back()] > lca_.info.dep[lca]) {
      if CEXP (alistw_c<G>) vt.add_arc(lca, st.back(), {});
      else vt.add_arc(lca, st.back());
      st.pop_back();
    }
    if (st.back() != lca) st.push_back(lca);
    st.push_back(x);
  }

 public:
  using tree_info_t = lca_hld<G>::tree_info_t;
  G vt;

  CEXPE virtual_tree(G CR tr) NE : tr(tr), lca_(tr), vt(0) {}

  CEXP void build(vecu& a) NE {
    sort(a, [&](u32 a, u32 b) NE { return lca_.info.dfn[a] < lca_.info.dfn[b]; });
    for (vt = G((u32)tr.g.size()), st.push_back(tr.root); u32 x : a) insert(x);
    while (st.size() > 1) {
      if CEXP (alistw_c<G>) vt.add_arc(st[st.size() - 2], st.back(), {});
      else vt.add_arc(st[st.size() - 2], st.back());
      st.pop_back();
    }
    st.pop_back();
  }
};

}  // namespace tifa_libs::graph
