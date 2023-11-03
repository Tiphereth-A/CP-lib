#ifndef TIFA_LIBS_GRAPH_ADJLIST
#define TIFA_LIBS_GRAPH_ADJLIST

#include "../util/util.hpp"

namespace tifa_libs::graph {

namespace adjlist_impl_ {

template <class T, bool isv = std::is_void_v<T>>
struct V;
template <class T>
struct V<T, false> {
  vec<T> v;
  V() {}
  template <class... Ts>
  V(Ts&&... args) : v(args...) {}
};
template <class T>
struct V<T, true> {
  V() {}
};

template <class T, bool isv = std::is_void_v<T>>
struct E;
template <class T>
struct E<T, false> {
  u32 to;
  T w;
  E() {}
  E(u32 v, T const& w) : to(v), w(w) {}
};
template <class T>
struct E<T, true> {
  u32 to;
  E() {}
  explicit E(u32 v) : to(v) {}
};

template <class VW = void, class EW = void>
class adjlist {
 protected:
  u32 m;
  vvec<E<EW>> g;
  V<VW> v;

 public:
  constexpr static bool HAS_VW = !std::is_void_v<VW>, HAS_EW = !std::is_void_v<EW>;
  //! vertex ID: [0, n)
  template <class... Ts>
  explicit adjlist(u32 n = 0, Ts&&... args_vw) : m(0), g(n), v(args_vw...) {}
  void reset_v_size(u32 n) { g.resize(n); }
  void clear() { g.clear(); }
  auto& v_weight() { return v.v; }
  auto v_weight() const { return v.v; }

  template <class... Ts>
  E<EW>& add_arc(u32 u, Ts&&... args) {
    ++m;
    g[u].emplace_back(args...);
    return g[u].back();
  }
  template <class... Ts>
  ptt<E<EW>&> add_edge(u32 u, u32 v, Ts&&... args) { return {add_arc(u, v, args...), add_arc(v, u, args...)}; }

  auto& operator[](u32 u) { return g[u]; }
  auto operator[](u32 u) const { return g[u]; }

  u32 v_size() const { return (u32)g.size(); }
  u32 arc_size() const { return m; }
};

}  // namespace adjlist_impl_

using adjlist_impl_::adjlist;

}  // namespace tifa_libs::graph

#endif