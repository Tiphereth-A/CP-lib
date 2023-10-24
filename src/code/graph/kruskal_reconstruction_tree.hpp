#ifndef TIFA_LIBS_GRAPH_KRUSKAL
#define TIFA_LIBS_GRAPH_KRUSKAL

#include "../ds/dsu_basic.hpp"
#include "../tree/tree.hpp"


namespace tifa_libs::graph {

//!! edge: w u v
template <class T>
inline std::pair<tree<void>, vec<T>> kruskal_re_tree(vec<std::tuple<T, u32, u32>> a, u32 n, vec<u32> node_w = vec<u32>()) {
  std::sort(a.begin(), a.end());
  if(node_w.size()) node_w.resize(2 * n - 1);
  tree<void> tr(2 * n - 1, node_w);
  vec<T> w_(2 * n - 1);
  ds::dsu_basic dsu(2 * n - 1);
  u32 m = n - 1, cnt = n;
  for (auto [w, u, v] : a) {
    u = dsu.find(u), v = dsu.find(v);
    if (u != v) {
        u32 t = cnt ++;
        w_[t] = w;
        tr.add_arc(t, u), tr.add_arc(t, v);
        dsu.merge(t, u), dsu.merge(t, v);
        --m;
    }
    if (m == 0) break;
  }
  tr.rt = cnt - 1;
  return {tr, w_};
}

}  // namespace tifa_libs::graph

#endif