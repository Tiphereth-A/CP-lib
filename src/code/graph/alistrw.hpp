#ifndef TIFALIBS_GRAPH_ALISTRW
#define TIFALIBS_GRAPH_ALISTRW

#include "alistw.hpp"

namespace tifa_libs::graph {

template <class T>
constexpr alistw<T> alistr(alistw<T> const& ag) {
  alistw<T> ret((u32)ag.g.size());
  for (u32 u = 0; u < ag.g.size(); ++u)
    for (auto&& [v, w] : ag.g[u]) ret.add_arc(v, u, -w);
  return ret;
}

}  // namespace tifa_libs::graph

#endif