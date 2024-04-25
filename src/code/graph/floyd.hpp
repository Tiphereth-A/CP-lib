#ifndef TIFALIBS_GRAPH_FLOYD
#define TIFALIBS_GRAPH_FLOYD

#include "amat.hpp"

namespace tifa_libs::graph {

//! will change input graph
template <class T, bool with_deg>
CEXP std::optional<amat<T, with_deg>> floyd(amat<T, with_deg>& g, T INF = std::numeric_limits<T>::max() / 2 - 1) {
  u32 n = (u32)g.g.size();
  flt_ (u32, k, 0, n)
    flt_ (u32, x, 0, n) {
      if (g.g[x][k] == INF) continue;
      flt_ (u32, y, 0, n) {
        if (g.g[k][y] == INF) continue;
        g.g[x][y] = min(g.g[x][y], g.g[x][k] + g.g[k][y]);
      }
    }
  flt_ (u32, x, 0, n)
    if (g.g[x][x] < 0) return {};
  return g;
}

}  // namespace tifa_libs::graph

#endif