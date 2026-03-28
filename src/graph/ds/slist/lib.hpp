#pragma once

#include "../graph_c/lib.hpp"

namespace tifa_libs {
namespace slist_impl_ {
template <class T, class... Info>
class slist_tag : public graph_info_impl_::graph_tag_base<Info...> {
  using base_t = graph_info_impl_::graph_tag_base<Info...>;
  using ET = graph_info_impl_::E<T>;
  vecu h;
  vecp<u32, ET> b;
  vecu e;
  bool builded = false;

 protected:
  using val_t = void;
  CEXPE slist_tag(u32 n) NE : base_t(n), h(n + 1), b{}, e{} {}
  CEXP slist_tag(u32 n, u32 m) NE : slist_tag(n) { b.reserve(m); }

 public:
  CEXP void add_arc(u32 u, auto&&... args) NE {
    if (!builded) [[likely]]
      base_t::add_arc(u, std::forward<decltype(args)>(args)...), b.emplace_back(u, ET{std::forward<decltype(args)>(args)...}), ++h[u];
    else assert(0);
  }
  CEXP u32 vsize() CNE { return (u32)h.size() - 1; }
  CEXP u32 esize() CNE { return (u32)e.size(); }
  CEXP u32 deg_out(u32 u) CNE { return h[u + 1] - h[u]; }
  CEXP void build() NE {
    if (builded || b.empty()) [[unlikely]]
      return;
    std::inclusive_scan(h.begin(), h.end(), h.begin());
    for (e.resize(b.size()); auto CR[u, v] : b) e[--h[u]] = v;
    builded = true;
  }

  CEXP auto operator[](u32 u) CNE { return spn{e.begin() + h[u], e.begin() + h[u + 1]}; }
};
}  // namespace slist_impl_
template <class Et = void, class... Info>
using slist = graph_impl_::graph<slist_impl_::slist_tag<Et, Info...>>;

}  // namespace tifa_libs
