#ifndef TIFALIBS_GRAPH_ALISTS
#define TIFALIBS_GRAPH_ALISTS

#include "../util/util.hpp"

namespace tifa_libs::graph {
namespace alists_impl_ {
template <class T, bool F = std::is_void<T>::value>
struct E;
template <class T>
struct E<T, false> {
  u32 to;
  T cost;
  CEXP E() = default;
  CEXP E(u32 v, cT_(T) c) NE : to(v), cost(c) {}
  CEXP operator u32() CNE { return to; }
};
template <class T>
struct E<T, true> {
  u32 to;
  CEXP E() = default;
  CEXP E(u32 v) NE : to(v) {}
  CEXP operator u32() CNE { return to; }
};
}  // namespace alists_impl_

template <class T = void, bool with_deg = false>
class alists {
  template <class I>
  struct Es {
    I b, e;
    CEXP I begin() CNE { return b; }
    CEXP I end() CNE { return e; }
    CEXP u32 size() CNE { return u32(e - b); }
    CEXP auto&& operator[](u32 i) CNE { return b[i]; }
  };
  using ET = alists_impl_::E<T>;
  vecu h;
  vecp<u32, ET> b;
  vec<ET> e;

 public:
  using w_t = T;
  u32 cnt_arc;
  vecu deg_in, deg_out;
  CEXP alists(u32 n) NE : h(n + 1), b(), e(), cnt_arc(0), deg_in(0), deg_out(0) {
    if CEXP (with_deg) deg_in.resize(n), deg_out.resize(n);
  }
  CEXP alists(u32 n, u32 m) NE : alists(n) { b.reserve(m); }
  //! DO NOT call this after called %build
  template <class... Ts>
  CEXP void add_arc(u32 u, Ts&&... args) NE { b.emplace_back(u, ET{std::forward<Ts>(args)...}), ++h[u]; }
  CEXP void add_edge(u32 u, u32 v) NE { add_arc(u, v), add_arc(v, u); }
  CEXP void build() NE {
    if (cnt_arc) return;
    std::inclusive_scan(h.begin(), h.end(), h.begin());
    for (e.resize(cnt_arc = (u32)b.size()); auto CR[u, e] : b) e[--h[u]] = e;
    if CEXP (with_deg)
      for (auto CR[u, e] : b) ++deg_out[u], ++deg_in[e.to];
  }
  CEXP u32 size() CNE { return h.size() - 1; }
  CEXP Es<TPN vec<ET>::iterator> operator[](u32 u) NE { return {e.begin() + h[u], e.begin() + h[u + 1]}; }
  CEXP const Es<TPN vec<ET>::const_iterator> operator[](u32 u) CNE { return {e.begin() + h[u], e.begin() + h[u + 1]}; }
  template <class F>
  CEXP void foreach(u32 u, F&& f) CNE {
    if CEXP (std::is_void_v<T>)
      for (auto to : (*this)[u]) f(to);
    else
      for (auto [to, cost] : (*this)[u]) f(to, cost);
  }
};

}  // namespace tifa_libs::graph

#endif