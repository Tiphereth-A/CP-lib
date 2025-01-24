#ifndef TIFALIBS_GRAPH_AMAT
#define TIFALIBS_GRAPH_AMAT

#include "../util/util.hpp"

namespace tifa_libs::graph {

template <class T, bool with_deg = false>
struct amat {
  using w_t = T;
  using val_t = vvec<T>;
  val_t g;
  u32 cnt_arc;
  vecu deg_in, deg_out;

  //! vertex ID: [0, n)
  CEXPE amat(u32 n, T const v = T{}) NE : g(n, vec<T>(n, v)), cnt_arc{0} {
    flt_ (u32, i, 0, n) g[i][i] = 0;
    if CEXP (with_deg) deg_in.resize(n), deg_out.resize(n);
  }

  CEXP void set_arc(u32 u, u32 v, cT_(T) w) NE {
    if (g[u][v] == w) return;
    u32 diff = u32(g[u][v] ? -!w : !!w);
    if CEXP (with_deg) deg_in[v] += diff, deg_out[u] += diff;
    cnt_arc += diff, g[u][v] = w;
  }
};

}  // namespace tifa_libs::graph

#endif