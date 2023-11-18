#ifndef TIFA_LIBS_GRAPH_EOGW
#define TIFA_LIBS_GRAPH_EOGW

#include "../util/util.hpp"

namespace tifa_libs::graph {

template <class T>
struct eogw {
  using weight_type = T;
  vec<u32> head;
  vvec<std::tuple<u32, T, u32>> e;

  //! vertex ID: [0, n)
  explicit eogw(u32 n = 0) : head(n, -1_u32) {}

  void add_arc(u32 u, u32 v, T const& w) {
    e[u].emplace_back(v, w, head[u]);
    head[u] = (u32)e[u].size() - 1;
  }
};

}  // namespace tifa_libs::graph

#endif