#ifndef TIFALIBS_GRAPH_EOG
#define TIFALIBS_GRAPH_EOG

#include "../util/util.hpp"

namespace tifa_libs::graph {

struct eog {
  vec<u32> head;
  vvec<ptt<u32>> e;

  //! vertex ID: [0, n)
  explicit eog(u32 n = 0) : head(n, -1_u32) {}

  void add_arc(u32 u, u32 v) {
    e[u].emplace_back(v, head[u]);
    head[u] = (u32)e[u].size() - 1;
  }
};

}  // namespace tifa_libs::graph

#endif