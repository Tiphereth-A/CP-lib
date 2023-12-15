#ifndef TIFALIBS_GRAPH_KRUSKAL
#define TIFALIBS_GRAPH_KRUSKAL

#include "../ds/dsu_basic.hpp"
#include "../tree/treew.hpp"

namespace tifa_libs::graph {

//! edge: w u v
//! edges MUST be sorted
template <class T>
constexpr treew<T> kruskal(vec<std::tuple<T, u32, u32>> sorted_a, u32 n) {
  treew<T> tr(n);
  ds::dsu_basic dsu(n);
  u32 m = n - 1;
  for (auto [w, u, v] : sorted_a) {
    if (dsu.merge(u, v)) tr.add_arc(u, v, w), tr.add_arc(v, u, w), --m;
    if (!m) break;
  }
  return tr;
}

}  // namespace tifa_libs::graph

#endif