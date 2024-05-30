#ifndef TIFALIBS_GRAPH_ALISTR
#define TIFALIBS_GRAPH_ALISTR

#include "alist.hpp"

namespace tifa_libs::graph {

template <bool with_deg>
CEXP alist<with_deg> alistr(alist<with_deg> CR ag) {
  alist ret((u32)ag.g.size());
  flt_ (u32, u, 0, (u32)ag.g.size())
    for (u32 v : ag.g[u]) ret.add_arc(v, u);
  return ret;
}

}  // namespace tifa_libs::graph

#endif