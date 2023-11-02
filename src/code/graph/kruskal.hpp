#ifndef TIFA_LIBS_GRAPH_KRUSKAL
#define TIFA_LIBS_GRAPH_KRUSKAL

#include "../ds/dsu_basic.hpp"
#include "../tree/tree.hpp"

namespace tifa_libs::graph {

//!! edge: w u v
//! MUST be sorted
template <class EW>
inline tree<void, EW> kruskal(vec<std::tuple<EW, u32, u32>> sorted_a, u32 n, u32 root = 0) {
  tree<void, EW> tr(n, root);
  ds::dsu_basic dsu(n);
  u32 m = n - 1;
  for (auto [w, u, v] : sorted_a) {
    if (dsu.merge(u, v)) tr.add_edge(u, v, w), --m;
    if (!m) break;
  }
  return tr;
}

}  // namespace tifa_libs::graph

#endif