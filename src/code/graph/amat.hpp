#ifndef TIFA_LIBS_GRAPH_AMAT
#define TIFA_LIBS_GRAPH_AMAT

#include "../util/util.hpp"

namespace tifa_libs::graph {

template <class T>
struct amat {
  using weight_type = T;
  using value_type = vvec<T>;
  value_type g;

  //! vertex ID: [0, n)
  explicit amat(u32 n, T const v = T{}) : g(n, vec<T>(n, v)) {
    for (u32 i = 0; i < n; ++i) g[i][i] = 0;
  }

  void set_arc(u32 u, u32 v, T const& w) { g[u][v] = w; }
};

}  // namespace tifa_libs::graph

#endif