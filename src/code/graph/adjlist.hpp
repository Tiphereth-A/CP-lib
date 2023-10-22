#ifndef TIFA_LIBS_GRAPH_ADJLIST
#define TIFA_LIBS_GRAPH_ADJLIST

#include "../util/util.hpp"

namespace tifa_libs::graph {

namespace adjlist_impl_ {

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

template <class T = void>
class adjlist {
  u32 m;
  vvec<E<T>> g;

 public:
  //! vertex ID: [0, n)
  explicit adjlist(u32 n) : m(0), g(n + 1) {}

  template <class... Args>
  E<T>& add_arc(u32 u, Args&&... args) {
    ++m;
    g[u].emplace_back(args...);
    return g[u].back();
  }

  auto& operator[](usz u) { return g[u]; }
  auto operator[](usz u) const { return g[u]; }

  usz v_size() const { return g.size(); }
  usz arc_size() const { return m; }
};

}  // namespace adjlist_impl_

using adjlist_impl_::adjlist;

}  // namespace tifa_libs::graph

#endif