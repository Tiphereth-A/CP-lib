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
  vecu deg_in;

  //! vertex ID: [0, n)
  explicit constexpr alistw(u32 n = 0) : g(n), cnt_arc(0), deg_in(0) {
    if constexpr (with_deg) deg_in.resize(n);
  }

  constexpr void add_arc(u32 u, u32 v, T const& w) {
    g[u].emplace_back(v, w), ++cnt_arc;
    if constexpr (with_deg) ++deg_in[v];
  }
};

}  // namespace tifa_libs::graph

#endif