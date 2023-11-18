#ifndef TIFA_LIBS_GRAPH_ALISTRW
#define TIFA_LIBS_GRAPH_ALISTRW

#include "alistw.hpp"

namespace tifa_libs::graph {

template <class T>
alistw<T> alistr(alistw<T> const& ag) {
  alistw<T> ret(ag.g.size());
  for (u32 u = 0; u < ag.g.size(); ++u)
    for (auto&& [v, w] : ag.g[u]) ret.add_arc(v, u, -w);
  return ret;
}

}  // namespace tifa_libs::graph

#endif