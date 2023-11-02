#ifndef TIFA_LIBS_TREE_VIRTUAL_TREE
#define TIFA_LIBS_TREE_VIRTUAL_TREE

#include "lca_hld.hpp"
#include "tree.hpp"

namespace tifa_libs::graph {

template <class EW = void>
class virtual_tree {
  tree<void, EW>& tr;
  lca_hld<void, EW> lca_;
  vec<u32> st;
  void insert(u32 x) {
    u32 lca = lca_(x, st.back());
    if (lca == st.back()) {
      st.push_back(x);
      return;
    }
    while (st.size() > 1 && tr.dep[st[st.size() - 2]] >= tr.dep[lca])
      vt.add_arc(st[st.size() - 2], st.back()), st.pop_back();
    if (tr.dep[st.back()] > tr.dep[lca]) vt.add_arc(lca, st.back()), st.pop_back();
    if (st.back() != lca) st.push_back(lca);
    st.push_back(x);
  }

 public:
  tree<> vt;
  virtual_tree(tree<void, EW>& tr) : tr(tr), lca_(tr), vt(tr.v_size()) {}
  void build(vec<u32>& a) {
    sort(a.begin(), a.end(), [&](u32 a, u32 b) { return tr.dfn[a] < tr.dfn[b]; }), vt.clear();
    st.push_back(tr.rt);
    for (auto x : a) insert(x);
    while (st.size() > 1) vt.add_arc(st[st.size() - 2], st.back()), st.pop_back();
    st.pop_back();
  }
};

}  // namespace tifa_libs::graph

#endif