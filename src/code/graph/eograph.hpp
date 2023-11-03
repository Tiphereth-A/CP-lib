#ifndef TIFA_LIBS_GRAPH_EOGRAPH
#define TIFA_LIBS_GRAPH_EOGRAPH

#include "../util/util.hpp"

namespace tifa_libs::graph {

namespace eograph_impl_ {

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
  u32 to, nxt;
  T w;
  E() {}
  E(u32 nxt, u32 v, T const& w) : to(v), nxt(nxt), w(w) {}
};
template <class T>
struct E<T, true> {
  u32 to, nxt;
  E() {}
  explicit E(u32 nxt, u32 v) : to(v), nxt(nxt) {}
};

template <class VW = void, class EW = void>
class eograph {
 protected:
  vec<u32> head;
  vec<E<EW>> e;
  V<VW> v;

 public:
  constexpr static bool HAS_VW = !std::is_void_v<VW>, HAS_EW = !std::is_void_v<EW>;
  //! vertex ID: [0, n)
  template <class... Ts>
  explicit eograph(u32 n = 0, Ts&&... args_vw) : head(n, -1_u32), e(), v(args_vw...) {}
  void reset(u32 n = 0) {
    clear();
    head.resize(n, -1_u32);
    v.resize(n);
  }
  void clear() {
    head.clear();
    e.clear();
    if constexpr (HAS_VW) v.v.clear();
  }
  auto& v_weight() { return v.v; }
  auto v_weight() const { return v.v; }

  template <class... Ts>
  u32 add_arc(u32 u, Ts&&... args) {
    e.emplace_back(head[u], args...);
    return head[u] = e.size() - 1;
  }
  template <class... Ts>
  ptt<u32> add_edge(u32 u, u32 v, Ts&&... args) { return {add_arc(u, v, args...), add_arc(v, u, args...)}; }

  auto& operator[](u32 eid) { return e[eid]; }
  auto operator[](u32 eid) const { return e[eid]; }

  u32 v_size() const { return (u32)head.size(); }
  u32 arc_size() const { return e.size(); }

  u32 rev_edge_id(u32 eid) const { return eid ^ 1; }

  template <class F>
  void foreach(u32 vid, F func) {
    for (u32 id = head[vid]; ~id; id = e[id].nxt) func(e[id]);
  }
  template <class F>
  void foreach_c(u32 vid, F func) const {
    for (u32 id = head[vid]; ~id; id = e[id].nxt) func(e[id]);
  }
};

}  // namespace eograph_impl_

using eograph_impl_::eograph;

}  // namespace tifa_libs::graph

#endif