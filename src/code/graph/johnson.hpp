#ifndef TIFALIBS_GRAPH_JOHNSON
#define TIFALIBS_GRAPH_JOHNSON

#include "bm.hpp"
#include "dijkstra.hpp"

namespace tifa_libs::graph {

//! edge: w u v
// @return dis, with dis[u][v] = minimum distance between u and v
template <class T>
CEXP std::optional<vvec<T>> johnson(u32 n, cT_(vec<std::tuple<T, u32, u32>>) arcs, T const INF = std::numeric_limits<T>::max() / 2 - 1) {
  using U = to_uint_t<T>;
  vvec<T> dis(n);
  alistw<T, false> fg(n);
  for (auto [w, u, v] : arcs) fg.add_arc(u, v, w);
  if CEXP (!is_sint_v<T>) {
    flt_ (u32, i, 0, n) dis[i] = dijkstra(fg, i, fn_0, INF);
  } else {
    fg.g.push_back({});
    flt_ (u32, i, 0, n) fg.add_arc(n, i, 0);
    auto h = bellman_ford(fg, n, fn_0, INF);
    if (!h) return {};
    alistw<U, false> fg2(n);
    for (auto [w, u, v] : arcs) fg2.add_arc(u, v, U(w - h.value()[v] + h.value()[u]));
    flt_ (u32, i, 0, n) {
      auto dis2 = dijkstra(fg2, i, fn_0, (U)INF);
      dis[i].resize(n);
      flt_ (u32, j, 0, n) dis[i][j] = dis2[j] == (U)INF ? INF : (T)dis2[j] + h.value()[j] - h.value()[i];
    }
  }
  return dis;
}

}  // namespace tifa_libs::graph

#endif