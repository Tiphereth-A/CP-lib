#ifndef TIFALIBS_GRAPH_ALISTRW
#define TIFALIBS_GRAPH_ALISTRW

#include "alistw.hpp"

namespace tifa_libs::graph {

template <class T, bool with_deg>
constexpr alistw<T, with_deg> alistrw(alistw<T, with_deg> const& ag) {
  alistw<T, with_deg> ret((u32)ag.g.size());
  for (u32 u = 0; u < ag.g.size(); ++u)
    for (auto&& [v, w] : ag.g[u]) ret.add_arc(v, u, w);
  return ret;
}

}  // namespace tifa_libs::graph

#endif