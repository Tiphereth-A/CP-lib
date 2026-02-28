#ifndef TIFALIBS_GRAPH_MST_KRUSKAL_RE_TREE_LIB
#define TIFALIBS_GRAPH_MST_KRUSKAL_RE_TREE_LIB

#include "../../../ds/dsu/basic/lib.hpp"
#include "../../../tree/ds/lib.hpp"

namespace tifa_libs::graph {

//! edge MUST be sorted
template <class EW>
CEXP std::pair<tree, vec<EW>> kruskal_re_tree(vec<edge_t<EW>> CR sorted_a, u32 n) NE {
  tree tr(2 * n - 1, 2 * n - 1);
  n = u32((tr.g.size() + 1) / 2);
  vec<EW> w_(2 * n - 1);
  ds::dsu_basic<false> dsu(2 * n - 1);
  u32 m = n - 1, cnt = n;
  for (auto [w, u, v] : sorted_a) {
    if (u = (u32)dsu.find(u), v = (u32)dsu.find(v); u != v) {
      const u32 t = cnt++;
      w_[t] = w, tr.add_arc(t, u), tr.add_arc(t, v), dsu.merge(t, u), dsu.merge(t, v), --m;
    }
    if (!m) break;
  }
  tr.root = cnt - 1;
  return {tr, w_};
}

}  // namespace tifa_libs::graph

#endif