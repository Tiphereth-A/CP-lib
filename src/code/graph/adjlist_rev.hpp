#ifndef TIFA_LIBS_GRAPH_ADJLIST_REV
#define TIFA_LIBS_GRAPH_ADJLIST_REV

#include "adjlist.hpp"

namespace tifa_libs::graph {

template <class T>
inline adjlist<T> adjlist_rev(adjlist<T> const& g) {
  adjlist<T> ret(g.v_size());
  for (u32 i = 0; i < g.v_size(); ++i)
    for (auto e : g[i])
      if constexpr (std::is_void_v<T>) ret.add_arc(e.to, i);
      else ret.add_arc(e.to, i, -e.w);
  return ret;
}

}  // namespace tifa_libs::graph

#endif