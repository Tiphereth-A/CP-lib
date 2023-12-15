#ifndef TIFALIBS_GRAPH_ALISTW
#define TIFALIBS_GRAPH_ALISTW

#include "../util/util.hpp"

namespace tifa_libs::graph {

template <class T>
struct alistw {
  using weight_type = T;
  using value_type = vvec<std::pair<u32, T>>;
  value_type g;

  //! vertex ID: [0, n)
  explicit constexpr alistw(u32 n = 0) : g(n) {}

  constexpr void add_arc(u32 u, u32 v, T const& w) { g[u].emplace_back(v, w); }
};

}  // namespace tifa_libs::graph

#endif