#ifndef TIFALIBS_GRAPH_AMAT
#define TIFALIBS_GRAPH_AMAT

#include "../util/util.hpp"

namespace tifa_libs::graph {

template <class T, bool with_deg = false>
struct amat {
  using weight_type = T;
  using value_type = vvec<T>;
  value_type g;
  u32 cnt_arc;
  vec<u32> deg_in, deg_out;

  //! vertex ID: [0, n)
  explicit constexpr amat(u32 n, T const v = T{}) : g(n, vec<T>(n, v)), cnt_arc(0), deg_in(0), deg_out(0) {
    for (u32 i = 0; i < n; ++i) g[i][i] = 0;
    if constexpr (with_deg) deg_in.resize(n), deg_out.resize(n);
  }

  constexpr void set_arc(u32 u, u32 v, T const& w) {
    if (g[u][v] >= g.size()) {
      ++cnt_arc;
      if constexpr (with_deg) ++deg_in[v], ++deg_out[u];
    }
    g[u][v] = w;
  }
};

}  // namespace tifa_libs::graph

#endif