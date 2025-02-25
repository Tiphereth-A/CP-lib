#ifndef TIFALIBS_GRAPH_MAKE_ALISTR
#define TIFALIBS_GRAPH_MAKE_ALISTR

#include "../util/traits.hpp"

namespace tifa_libs::graph {

template <alist_c G>
CEXP auto make_alistr(G CR g) NE {
  const u32 n = g.size();
  G ret(n);
  flt_ (u32, u, 0, n)
    if CEXP (alistw_c<G>)
      for (auto&& [v, w] : g[u]) ret.add_arc(v, u, w);
    else
      for (auto v : g[u]) ret.add_arc(v, u);
  ret.build();
  return ret;
}

}  // namespace tifa_libs::graph

#endif