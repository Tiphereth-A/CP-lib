#ifndef TIFA_LIBS_GRAPH_FLOYD
#define TIFA_LIBS_GRAPH_FLOYD

#include "adjmat.hpp"

namespace tifa_libs::graph {

template <class W>
std::optional<adjmat<W>> floyd(adjmat<W> g, W INF = std::numeric_limits<W>::max() / 2 - 1) {
  u32 n = g.v_size();
  for (u32 k = 0; k < n; ++k)
    for (u32 x = 0; x < n; ++x) {
      if (g[x][k] == INF) continue;
      for (u32 y = 0; y < n; ++y) {
        if (g[k][y] == INF) continue;
        g[x][y] = std::min(g[x][y], g[x][k] + g[k][y]);
      }
    }
  for (u32 x = 0; x < n; ++x)
    if (g[x][x] < 0) return {};
  return g;
}

}  // namespace tifa_libs::graph

#endif