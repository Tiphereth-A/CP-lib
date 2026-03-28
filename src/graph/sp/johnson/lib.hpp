#pragma once

#include "../../ds/alist/lib.hpp"
#include "../bm/lib.hpp"
#include "../dijkstra/lib.hpp"

namespace tifa_libs {

// @return dis, with dis[u][v] = minimum distance between u and v
template <class T>
CEXP auto johnson(u32 n, vec<edge_t<T>> CR arcs, T const INF = inf_v<T>) NE {
  using U = to_uint_t<T>;
  std::optional<vvec<T>> ret;

  if CEXP (!sint_c<T>) {
    alist<T> g(n);
    for (auto [w, u, v] : arcs) g.add_arc(u, v, w);
    ret->emplace(vvec<T>(n));
    flt_ (u32, i, 0, n) ret.value()[i] = dijkstra(g, i, fn_0, INF);
  } else {
    alist<T> g(n + 1);
    for (auto [w, u, v] : arcs) g.add_arc(u, v, w);
    flt_ (u32, i, 0, n) g.add_arc(n, i, 0);
    auto h = bellman_ford(g, n, fn_0, INF);
    if (!h) return ret;
    ret.emplace(vvec<T>(n));
    alist<U> fg2(n);
    for (auto [w, u, v] : arcs) fg2.add_arc(u, v, U(w - h.value()[v] + h.value()[u]));
    flt_ (u32, i, 0, n) {
      auto dis2 = dijkstra(fg2, i, fn_0, (U)INF);
      ret.value()[i].resize(n);
      flt_ (u32, j, 0, n) ret.value()[i][j] = dis2[j] == (U)INF ? INF : (T)dis2[j] + h.value()[j] - h.value()[i];
    }
  }
  return ret;
}

}  // namespace tifa_libs
