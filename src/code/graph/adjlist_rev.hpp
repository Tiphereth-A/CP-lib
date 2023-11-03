#ifndef TIFA_LIBS_GRAPH_ADJLIST_REV
#define TIFA_LIBS_GRAPH_ADJLIST_REV

#include "adjlist.hpp"

namespace tifa_libs::graph {

template <class VW, class EW>
adjlist<VW, EW> adjlist_rev(adjlist<VW, EW> const& g) {
  using graph_t = adjlist<VW, EW>;
  graph_t ret(g.v_size());
  if constexpr (graph_t::HAS_VW) ret.v_weight() = g.v_weight();
  for (u32 i = 0; i < g.v_size(); ++i)
    for (auto e : g[i])
      if constexpr (graph_t::HAS_EW) ret.add_arc(e.to, i, -e.w);
      else ret.add_arc(e.to, i);
  return ret;
}

}  // namespace tifa_libs::graph

#endif