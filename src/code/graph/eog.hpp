#ifndef TIFALIBS_GRAPH_EOG
#define TIFALIBS_GRAPH_EOG

#include "../util/util.hpp"

namespace tifa_libs::graph {

template <bool with_deg = false>
struct eog {
  vecu head;
  vecptu e;
  u32 cnt_arc;
  vecu deg_in, deg_out;
  //! vertex ID: [0, n)
  CEXPE eog(u32 n = 0) : head(n, -1_u32), e(), cnt_arc(0), deg_in(0), deg_out(0) {
    if CEXP (with_deg) deg_in.resize(n), deg_out.resize(n);
  }
  CEXP void add_arc(u32 u, u32 v) {
    e.emplace_back(v, head[u]), head[u] = u32(e.size() - 1);
    if CEXP (++cnt_arc; with_deg) ++deg_in[v], ++deg_out[u];
  }
  CEXP void pop_startwith(u32 now) {
    if CEXP (--cnt_arc; with_deg) --deg_in[e[head[now]].first], --deg_out[now];
    head[now] = e[head[now]].second;
  }
};
template <class T, bool with_deg = false>
struct eogw {
  // clang-format off
  struct TIFA { u32 to; T w; u32 nxt; };
  // clang-format on
  using w_t = T;
  vecu head;
  vec<TIFA> e;
  u32 cnt_arc;
  vecu deg_in, deg_out;
  //! vertex ID: [0, n)
  CEXPE eogw(u32 n = 0) : head(n, -1_u32), e(), cnt_arc(0), deg_in(0), deg_out(0) {
    if CEXP (with_deg) deg_in.resize(n), deg_out.resize(n);
  }
  CEXP void add_arc(u32 u, u32 v, cT_(T) w) {
    e.emplace_back(v, w, head[u]), head[u] = u32(e.size() - 1);
    if CEXP (++cnt_arc; with_deg) ++deg_in[v], ++deg_out[u];
  }
  CEXP void pop_startwith(u32 now) {
    if CEXP (--cnt_arc; with_deg) --deg_in[e[head[now]].first], --deg_out[now];
    head[now] = e[head[now]].second;
  }
};

}  // namespace tifa_libs::graph

#endif