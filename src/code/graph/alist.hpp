#ifndef TIFALIBS_GRAPH_ALIST
#define TIFALIBS_GRAPH_ALIST

#include "../util/util.hpp"

namespace tifa_libs::graph {

template <bool with_deg = false>
struct alist {
  using w_t = void;
  vvecu g;
  u32 cnt_arc;
  vecu deg_in, deg_out;
  //! vertex ID: [0, n)
  CEXPE alist(u32 n = 0) : g(n), cnt_arc(0), deg_in(0), deg_out(0) {
    if CEXP (with_deg) deg_in.resize(n), deg_out.resize(n);
  }
  CEXP void add_arc(u32 u, u32 v) {
    g[u].push_back(v);
    if CEXP (++cnt_arc; with_deg) ++deg_in[v], ++deg_out[u];
  }
  CEXP void build() const {}
  CEXP u32 size() const { return (u32)g.size(); }
  CEXP auto& operator[](u32 u) { return g[u]; }
  CEXP auto CR operator[](u32 u) const { return g[u]; }
};
template <class T, bool with_deg = false>
struct alistw {
  using w_t = T;
  vvecp<u32, T> g;
  u32 cnt_arc;
  vecu deg_in, deg_out;
  //! vertex ID: [0, n)
  CEXPE alistw(u32 n = 0) : g(n), cnt_arc(0), deg_in(0), deg_out(0) {
    if CEXP (with_deg) deg_in.resize(n), deg_out.resize(n);
  }
  CEXP void add_arc(u32 u, u32 v, cT_(T) w) {
    g[u].emplace_back(v, w);
    if CEXP (++cnt_arc; with_deg) ++deg_in[v], ++deg_out[u];
  }
  CEXP void build() const {}
  CEXP u32 size() const { return (u32)g.size(); }
  CEXP auto& operator[](u32 u) { return g[u]; }
  CEXP auto CR operator[](u32 u) const { return g[u]; }
};

}  // namespace tifa_libs::graph

#endif