#pragma once

#include "../graph_c/lib.hpp"

namespace tifa_libs {
namespace alist_impl_ {
template <class T, class... Info>
class alist_tag : public graph_info_impl_::graph_tag_base<Info...> {
  using base_t = graph_info_impl_::graph_tag_base<Info...>;
  vvec<graph_info_impl_::E<T>> g;

 protected:
  using val_t = T;
  CEXPE alist_tag(u32 n) NE : base_t(n), g(n) {}

 public:
  CEXP void build() CNE {}
  CEXP void add_arc(u32 u, auto&&... args) NE { base_t::add_arc(u, std::forward<decltype(args)>(args)...), g[u].emplace_back(std::forward<decltype(args)>(args)...); }
  CEXP u32 vsize() CNE { return (u32)g.size(); }
  CEXP u32 deg_out(u32 u) CNE { return (u32)g[u].size(); }

  CEXP auto CR operator[](u32 u) CNE { return g[u]; }
  CEXP auto& operator[](u32 u) NE { return g[u]; }
};
}  // namespace alist_impl_
template <class Et = void, class... Info>
using alist = graph_impl_::graph<alist_impl_::alist_tag<Et, Info...>>;

}  // namespace tifa_libs
