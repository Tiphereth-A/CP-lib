#ifndef TIFALIBS_GRAPH_JOHNSON
#define TIFALIBS_GRAPH_JOHNSON

#include "alist.hpp"
#include "bm.hpp"
#include "dijkstra.hpp"

namespace tifa_libs::graph {

// @return dis, with dis[u][v] = minimum distance between u and v
template <class T>
CEXP auto johnson(u32 n, vec<edge_t<T>> CR arcs, T const INF = inf_v<T>) NE {
  using U = to_uint_t<T>;
  std::optional ret{vvec<T>(n)};
  alistw<T> g(n);
  for (auto [w, u, v] : arcs) g.add_arc(u, v, w);
  if CEXP (!sint_c<T>)
    flt_ (u32, i, 0, n) ret.value()[i] = dijkstra(g, i, fn_0, INF);
  else {
    g.g.push_back({});
    flt_ (u32, i, 0, n) g.add_arc(n, i, 0);
    auto h = bellman_ford(g, n, fn_0, INF);
    if (!h) {
      ret = std::nullopt;
      return ret;
    }
    alistw<U> fg2(n);
    for (auto [w, u, v] : arcs) fg2.add_arc(u, v, U(w - h.value()[v] + h.value()[u]));
    flt_ (u32, i, 0, n) {
      auto dis2 = dijkstra(fg2, i, fn_0, (U)INF);
      ret.value()[i].resize(n);
      flt_ (u32, j, 0, n) ret.value()[i][j] = dis2[j] == (U)INF ? INF : (T)dis2[j] + h.value()[j] - h.value()[i];
    }
  }
  return ret;
}

}  // namespace tifa_libs::graph

#endif