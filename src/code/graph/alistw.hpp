#ifndef TIFALIBS_GRAPH_ALISTW
#define TIFALIBS_GRAPH_ALISTW

#include "../util/util.hpp"

namespace tifa_libs::graph {

template <class T, bool with_deg = false>
struct alistw {
  using weight_type = T;
  using value_type = vvecp<u32, T>;
  value_type g;
  u32 cnt_arc;
  vecu deg_in, deg_out;

  //! vertex ID: [0, n)
  explicit CEXP alistw(u32 n = 0) : g(n), cnt_arc(0) {
    if CEXP (with_deg) deg_in.resize(n), deg_out.resize(n);
  }

  CEXP void add_arc(u32 u, u32 v, cT_(T) w) {
    g[u].emplace_back(v, w), ++cnt_arc;
    if CEXP (with_deg) ++deg_in[v], ++deg_out[u];
  }
};

}  // namespace tifa_libs::graph

#endif