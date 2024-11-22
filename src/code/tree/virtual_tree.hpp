#ifndef TIFALIBS_TREE_VIRTUAL_TREE
#define TIFALIBS_TREE_VIRTUAL_TREE

#include "lca_hld.hpp"
#include "tree.hpp"

namespace tifa_libs::graph {

class virtual_tree {
  tree CR tr;
  lca_hld lca_;
  vecu st;

  CEXP void insert(u32 x) {
    u32 lca = lca_(x, st.back());
    if (lca == st.back()) return st.push_back(x);
    while (st.size() > 1 && lca_.info.dep[st[st.size() - 2]] >= lca_.info.dep[lca]) vt.add_arc(st[st.size() - 2], st.back()), st.pop_back();
    if (lca_.info.dep[st.back()] > lca_.info.dep[lca]) vt.add_arc(lca, st.back()), st.pop_back();
    if (st.back() != lca) st.push_back(lca);
    st.push_back(x);
  }

 public:
  using tree_info_t = lca_hld::tree_info_t;
  tree vt;

  CEXPE virtual_tree(tree CR tr, tree_info_t CR info) : tr(tr), lca_(tr, info), vt((u32)tr.g.size()) {}

  CEXP void build(vecu& a) {
    std::ranges::sort(a, [&](u32 a, u32 b) { return lca_.info.dfn[a] < lca_.info.dfn[b]; });
    for (vt.g.clear(), st.push_back(tr.root); u32 x : a) insert(x);
    while (st.size() > 1) vt.add_arc(st[st.size() - 2], st.back()), st.pop_back();
    st.pop_back();
  }
};

}  // namespace tifa_libs::graph

#endif