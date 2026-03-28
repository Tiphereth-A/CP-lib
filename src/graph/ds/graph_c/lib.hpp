#pragma once

#include "../../../util/traits/others/lib.hpp"

namespace tifa_libs {
namespace graph_info_impl_ {
struct graph_info_tag_base {};
template <class... Info>
requires(std::derived_from<Info, graph_info_tag_base> && ...)
struct graph_tag_base : Info... {
  CEXP graph_tag_base(auto&&... args) NE : Info(std::forward<decltype(args)>(args)...)... {}

 protected:
  CEXP void add_arc(auto&&... args) NE { (Info::add_arc(std::forward<decltype(args)>(args)...), ...); }
  CEXP void del_arc(auto&&... args) NE { (Info::del_arc(std::forward<decltype(args)>(args)...), ...); }
};
template <class T, class = std::is_void<T>::type>
struct E;
template <class T>
struct E<T, std::false_type> {
  u32 to;
  T cost;
  CEXP E() = default;
  CEXP E(u32 v, cT_(T) c) NE : to(v), cost(c) {}
  CEXP operator u32() CNE { return to; }
};
template <class T>
struct E<T, std::true_type> {
  u32 to;
  CEXP E() = default;
  CEXP E(u32 v) NE : to(v) {}
  CEXP operator u32() CNE { return to; }
};
}  // namespace graph_info_impl_

namespace graph_impl_ {
template <class etag_t>
struct graph : etag_t {
  using Et = etag_t::val_t;

  CEXP graph() = default;
  CEXPE graph(u32 n, auto&&... e_args) NE : etag_t(n, std::forward<decltype(e_args)>(e_args)...) {}

  CEXP void add_edge(u32 u, u32 v, auto&&... args) NE { etag_t::add_arc(u, v, std::forward<decltype(args)>(args)...), etag_t::add_arc(v, u, std::forward<decltype(args)>(args)...); }
  template <class F>
  CEXP void foreach(u32 u, F&& f) CNE {
    if CEXP (std::is_void_v<Et>)
      for (auto v : (*this)[u]) f(v);
    else
      for (auto [v, w] : (*this)[u]) f(v, w);
  }
};
}  // namespace graph_impl_

// clang-format off
#define CONCEPT_GRAPH(name, base)                                                         \
template <class T> concept name##_c = specialized_from_v<T, base>;                     \
template <class T> concept u##name##_c = name##_c<T> && std::same_as<TPN T::Et, void>; \
template <class T> concept w##name##_c = name##_c<T> && !std::same_as<TPN T::Et, void>
// clang-format on
CONCEPT_GRAPH(graph, graph_impl_::graph);

}  // namespace tifa_libs
