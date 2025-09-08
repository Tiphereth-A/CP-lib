#ifndef TIFALIBS_GRAPH_ALIST
#define TIFALIBS_GRAPH_ALIST

#include "../util/alias_others.hpp"

namespace tifa_libs::graph {

template <bool with_deg = false>
struct alist {
  using w_t = void;
  vvecu g;
  u32 cnt_arc;
  vecu deg_in, deg_out;
  //! vertex ID: [0, n)
  CEXPE alist(u32 n = 0) NE : g(n), cnt_arc{0}, deg_in(0), deg_out(0) {
    if CEXP (with_deg) deg_in.resize(n), deg_out.resize(n);
  }
  CEXP void add_arc(u32 u, u32 v) NE {
    g[u].push_back(v);
    if CEXP (++cnt_arc; with_deg) ++deg_in[v], ++deg_out[u];
  }
  CEXP void add_edge(u32 u, u32 v) NE { add_arc(u, v), add_arc(v, u); }
  CEXP void build() CNE {}
  CEXP u32 size() CNE { return (u32)g.size(); }
  CEXP auto& operator[](u32 u) NE { return g[u]; }
  CEXP auto CR operator[](u32 u) CNE { return g[u]; }
  template <class F>
  requires requires(F f, u32 v) { f(v); }
  CEXP void foreach(u32 u, F&& f) CNE {
    for (auto v : g[u]) f(v);
  }
};
template <class T, bool with_deg = false>
struct alistw {
  using w_t = T;
  vvecp<u32, T> g;
  u32 cnt_arc;
  vecu deg_in, deg_out;
  //! vertex ID: [0, n)
  CEXPE alistw(u32 n = 0) NE : g(n), cnt_arc{0}, deg_in(0), deg_out(0) {
    if CEXP (with_deg) deg_in.resize(n), deg_out.resize(n);
  }
  CEXP void add_arc(u32 u, u32 v, cT_(T) w) NE {
    g[u].emplace_back(v, w);
    if CEXP (++cnt_arc; with_deg) ++deg_in[v], ++deg_out[u];
  }
  CEXP void add_edge(u32 u, u32 v, cT_(T) w) NE { add_arc(u, v, w), add_arc(v, u, w); }
  CEXP void build() CNE {}
  CEXP u32 size() CNE { return (u32)g.size(); }
  CEXP auto& operator[](u32 u) NE { return g[u]; }
  CEXP auto CR operator[](u32 u) CNE { return g[u]; }
  template <class F>
  requires requires(F f, u32 v, T w) { f(v, w); }
  CEXP void foreach(u32 u, F&& f) CNE {
    for (auto [v, w] : g[u]) f(v, w);
  }
};

}  // namespace tifa_libs::graph

#endif