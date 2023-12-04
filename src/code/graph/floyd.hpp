#ifndef TIFALIBS_GRAPH_FLOYD
#define TIFALIBS_GRAPH_FLOYD

#include "amat.hpp"

namespace tifa_libs::graph {

//! will change input graph
template <class T>
std::optional<amat<T>> floyd(amat<T>& g, T INF = std::numeric_limits<T>::max() / 2 - 1) {
  u32 n = (u32)g.g.size();
  for (u32 k = 0; k < n; ++k)
    for (u32 x = 0; x < n; ++x) {
      if (g.g[x][k] == INF) continue;
      for (u32 y = 0; y < n; ++y) {
        if (g.g[k][y] == INF) continue;
        g.g[x][y] = std::min(g.g[x][y], g.g[x][k] + g.g[k][y]);
      }
    }
  for (u32 x = 0; x < n; ++x)
    if (g.g[x][x] < 0) return {};
  return g;
}

}  // namespace tifa_libs::graph

#endif