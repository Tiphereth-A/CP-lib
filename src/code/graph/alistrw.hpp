#ifndef TIFALIBS_GRAPH_ALISTRW
#define TIFALIBS_GRAPH_ALISTRW

#include "alistw.hpp"

namespace tifa_libs::graph {

template <class T, bool with_deg>
CEXP alistw<T, with_deg> alistrw(alistw<T, with_deg> CR ag) {
  alistw<T, with_deg> ret((u32)ag.g.size());
  flt_ (u32, u, 0, (u32)ag.g.size())
    for (auto&& [v, w] : ag.g[u]) ret.add_arc(v, u, w);
  return ret;
}

}  // namespace tifa_libs::graph

#endif