#ifndef TIFA_LIBS_GRAPH_ALISTR
#define TIFA_LIBS_GRAPH_ALISTR

#include "alist.hpp"

namespace tifa_libs::graph {

inline alist alistr(alist const& ag) {
  alist ret(ag.g.size());
  for (u32 u = 0; u < ag.g.size(); ++u)
    for (u32 v : ag.g[u]) ret.add_arc(v, u);
  return ret;
}

}  // namespace tifa_libs::graph

#endif