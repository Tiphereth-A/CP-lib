#ifndef TIFA_LIBS_GRAPH_ADJMAT
#define TIFA_LIBS_GRAPH_ADJMAT

#include "../util/util.hpp"

namespace tifa_libs::graph {

template <class T = u32>
class adjmat {
  u32 m;
  vvec<T> g;

 public:
  //! vertex ID: [0, n)
  explicit adjmat(u32 n, T val = T{}) : m(0), g(n, vec<T>(n, val)) {
    for (u32 i = 0; i < n; ++i) g[i][i] = 0;
  }

  T& add_arc(u32 u, u32 v, T const& w) {
    ++m;
    return g[u][v] = w;
  }

  auto& operator[](usz u) { return g[u]; }
  auto operator[](usz u) const { return g[u]; }

  auto& data() { return g; }
  auto data() const { return g; }
  auto& operator()(usz u, usz v) { return g[u][v]; }
  auto operator()(usz u, usz v) const { return g[u][v]; }

  usz v_size() const { return g.size(); }
  usz arc_size() const { return m; }
};

}  // namespace tifa_libs::graph

#endif