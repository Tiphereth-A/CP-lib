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
  vecu deg_in, deg_out;

  //! vertex ID: [0, n)
  explicit CEXP amat(u32 n, T const v = T{}) : g(n, vec<T>(n, v)), cnt_arc(0), deg_in(0), deg_out(0) {
    flt_ (u32, i, 0, n) g[i][i] = 0;
    if CEXP (with_deg) deg_in.resize(n), deg_out.resize(n);
  }

  CEXP void set_arc(u32 u, u32 v, cT_(T) w) {
    if (g[u][v] == w) return;
    ++cnt_arc;
    g[u][v] = w;
    if CEXP (with_deg) ++deg_in[v], ++deg_out[u];
  }
};

}  // namespace tifa_libs::graph

#endif