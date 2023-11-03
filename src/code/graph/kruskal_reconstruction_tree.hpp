#ifndef TIFA_LIBS_GRAPH_KRUSKAL_RECONSTRUCTION_TREE
#define TIFA_LIBS_GRAPH_KRUSKAL_RECONSTRUCTION_TREE

#include "../ds/dsu_basic.hpp"
#include "../tree/tree.hpp"

namespace tifa_libs::graph {

namespace kruskal_re_tree_impl_ {

template <class VW, class EW>
std::pair<tree<VW>, vec<EW>> run_(tree<VW>& tr, vec<std::tuple<EW, u32, u32>> const& sorted_a) {
  u32 n = (tr.v_size() + 1) / 2;
  vec<EW> w_(2 * n - 1);
  ds::dsu_basic dsu(2 * n - 1);
  u32 m = n - 1, cnt = n;
  for (auto [w, u, v] : sorted_a) {
    u = (u32)dsu.find(u), v = (u32)dsu.find(v);
    if (u != v) {
      u32 t = cnt++;
      w_[t] = w;
      tr.add_arc(t, u), tr.add_arc(t, v);
      dsu.merge(t, u), dsu.merge(t, v);
      --m;
    }
    if (!m) break;
  }
  tr.rt = cnt - 1;
  return {tr, w_};
}

}  // namespace kruskal_re_tree_impl_

//!! edge: w u v
//! MUST be sorted
template <class VW, class EW>
std::pair<tree<VW>, vec<EW>> kruskal_re_tree(vec<std::tuple<EW, u32, u32>> const& sorted_a, u32 n, vec<VW> node_w) {
  tree<VW> tr(2 * n - 1, 2 * n - 1, node_w);
  return kruskal_re_tree_impl_::run_(tr, sorted_a);
}
//!! edge: w u v
//! MUST be sorted
template <class VW, class EW, std::enable_if_t<std::is_void_v<VW>>* = nullptr>
std::pair<tree<VW>, vec<EW>> kruskal_re_tree(vec<std::tuple<EW, u32, u32>> const& sorted_a, u32 n) {
  tree<> tr(2 * n - 1, 2 * n - 1);
  return kruskal_re_tree_impl_::run_(tr, sorted_a);
}

}  // namespace tifa_libs::graph

#endif