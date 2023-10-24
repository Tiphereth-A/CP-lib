#ifndef TIFA_LIBS_GRAPH_KRUSKAL
#define TIFA_LIBS_GRAPH_KRUSKAL

#include "../ds/dsu_basic.hpp"
#include "../tree/tree.hpp"


namespace tifa_libs::graph {

//!! edge: w u v
template <class T>
inline tree<T> kruskal(vec<std::tuple<T, u32, u32>> a, u32 n, u32 root = 0) {
  std::sort(a.begin(), a.end());
  tree<T> tr(n, root);
  ds::dsu_basic dsu(n);
  u32 m = n - 1;
  for (auto [w, u, v] : a) {
    if (dsu.merge(u, v)) tr.add_edge(u, v, w), --m;
    if (m == 0) break;
  }
  return tr;
}

}  // namespace tifa_libs::graph

#endif