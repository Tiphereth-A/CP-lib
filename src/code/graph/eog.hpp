#ifndef TIFALIBS_GRAPH_EOG
#define TIFALIBS_GRAPH_EOG

#include "../util/util.hpp"

namespace tifa_libs::graph {

template <bool with_deg = false>
struct eog {
  using w_t = void;
  vecu head;
  vecptu e;
  u32 cnt_arc;
  vecu deg_in, deg_out;
  //! vertex ID: [0, n)
  CEXPE eog(u32 n = 0) NE : head(n, -1_u32), e(), cnt_arc{0}, deg_in(0), deg_out(0) {
    if CEXP (with_deg) deg_in.resize(n), deg_out.resize(n);
  }
  CEXP u32 size() CNE { return (u32)head.size(); }
  CEXP void add_arc(u32 u, u32 v) NE {
    e.emplace_back(v, head[u]), head[u] = u32(e.size() - 1);
    if CEXP (++cnt_arc; with_deg) ++deg_in[v], ++deg_out[u];
  }
  CEXP void add_edge(u32 u, u32 v) NE { add_arc(u, v), add_arc(v, u); }
  CEXP void pop_startwith(u32 now) NE {
    if CEXP (--cnt_arc; with_deg) --deg_in[e[head[now]].first], --deg_out[now];
    head[now] = e[head[now]].second;
  }
  CEXP auto& operator[](u32 u) NE { return e[u]; }
  CEXP auto CR operator[](u32 u) CNE { return e[u]; }
  template <class F>
  requires requires(F f, u32 eid, u32 to, u32 next) { f(eid, to, next); }
  CEXP void foreach(u32 u, F&& f) CNE {
    for (u32 i = head[u]; ~i; i = e[i].second) f(i, e[i].first, e[i].second);
  }
};
template <class T, bool with_deg = false>
struct eogw {
  using w_t = T;
  // clang-format off
  struct TIFA { u32 to; T w; u32 nxt; };
  // clang-format on
  vecu head;
  vec<TIFA> e;
  u32 cnt_arc;
  vecu deg_in, deg_out;
  //! vertex ID: [0, n)
  CEXPE eogw(u32 n = 0) NE : head(n, -1_u32), e(), cnt_arc{0}, deg_in(0), deg_out(0) {
    if CEXP (with_deg) deg_in.resize(n), deg_out.resize(n);
  }
  CEXP u32 size() CNE { return (u32)head.size(); }
  CEXP void add_arc(u32 u, u32 v, cT_(T) w) NE {
    e.emplace_back(v, w, head[u]), head[u] = u32(e.size() - 1);
    if CEXP (++cnt_arc; with_deg) ++deg_in[v], ++deg_out[u];
  }
  CEXP void add_edge(u32 u, u32 v, cT_(T) w) NE { add_arc(u, v, w), add_arc(v, u, w); }
  CEXP void pop_startwith(u32 now) NE {
    if CEXP (--cnt_arc; with_deg) --deg_in[e[head[now]].first], --deg_out[now];
    head[now] = e[head[now]].second;
  }
  CEXP auto& operator[](u32 u) NE { return e[u]; }
  CEXP auto CR operator[](u32 u) CNE { return e[u]; }
  template <class F>
  requires requires(F f, u32 eid, u32 to, T w, u32 next) { f(eid, to, next, w); }
  CEXP void foreach(u32 u, F&& f) CNE {
    for (u32 i = head[u]; ~i; i = e[i].second) f(i, e[i].to, e[i].w, e[i].nxt);
  }
};

}  // namespace tifa_libs::graph

#endif