#ifndef TIFALIBS_GRAPH_EOGW
#define TIFALIBS_GRAPH_EOGW

#include "../util/util.hpp"

namespace tifa_libs::graph {

template <class T, bool with_deg = false>
struct eogw {
  using weight_type = T;
  vec<u32> head;
  vec<std::tuple<u32, T, u32>> e;
  u32 cnt_arc;
  vec<u32> deg_in, deg_out;

  //! vertex ID: [0, n)
  explicit constexpr eogw(u32 n = 0) : head(n, -1_u32), e(), cnt_arc(0), deg_in(0), deg_out(0) {
    if constexpr (with_deg) deg_in.resize(n), deg_out.resize(n);
  }

  constexpr void add_arc(u32 u, u32 v, T const& w) {
    e.emplace_back(v, w, head[u]);
    head[u] = u32(e.size() - 1), ++cnt_arc;
    if constexpr (with_deg) ++deg_in[v], ++deg_out[u];
  }
  constexpr void pop_startwith(u32 now) {
    if constexpr (with_deg) --deg_in[e[head[now]].first], --deg_out[now];
    head[now] = e[head[now]].second, --cnt_arc;
  }
};

}  // namespace tifa_libs::graph

#endif