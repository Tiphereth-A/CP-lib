#ifndef TIFA_LIBS_GRAPH_FLOYD
#define TIFA_LIBS_GRAPH_FLOYD

#include "adjmat.hpp"

namespace tifa_libs::graph {

template <class W>
std::optional<adjmat<W>> floyd(adjmat<W> g) {
  u32 n = g.v_size();
  for (u32 k = 0; k < n; ++k)
    for (u32 x = 0; x < n; ++x) {
      for (u32 y = 0; y < n; ++y) g[x][y] = std::min(g[x][y], g[x][k] + g[k][y]);
      if (g[x][x] < 0) return {};
    }
  return g;
}

}  // namespace tifa_libs::graph

#endif