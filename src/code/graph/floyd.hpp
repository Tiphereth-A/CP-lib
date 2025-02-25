#ifndef TIFALIBS_GRAPH_FLOYD
#define TIFALIBS_GRAPH_FLOYD

#include "../util/traits.hpp"
#include "amat.hpp"

namespace tifa_libs::graph {

//! will change input graph
// @return false if invalid (has nagative cycle), otherwise true
template <class T, bool with_deg>
CEXP bool floyd(amat<T, with_deg>& g, T INF = inf_v<T>) NE {
  u32 n = (u32)g.g.size();
  flt_ (u32, k, 0, n)
    flt_ (u32, x, 0, n)
      if (g.g[x][k] < INF)
        flt_ (u32, y, 0, n)
          if (g.g[k][y] < INF) g.g[x][y] = min(g.g[x][y], g.g[x][k] + g.g[k][y]);
  flt_ (u32, x, 0, n)
    if (g.g[x][x] < 0) return 0;
  return 1;
}

}  // namespace tifa_libs::graph

#endif