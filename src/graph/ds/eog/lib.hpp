#pragma once

#include "../graph_c/lib.hpp"

namespace tifa_libs {
namespace eog_impl_ {
template <class T, class... Info>
class eog_tag : public graph_info_impl_::graph_tag_base<Info...> {
  using base_t = graph_info_impl_::graph_tag_base<Info...>;
  using ET = graph_info_impl_::E<T>;
  struct iter_ {
    vecp<ET, u32> CR e;
    u32 i;

    iter_(vecp<ET, u32> CR e, u32 i) NE : e(e), i(i) {}

    CEXP auto begin() CNE { return iter_{e, i}; }
    CEXP auto end() CNE { return iter_{e, -1_u32}; }

    CEXP auto operator*() CNE { return e[i].first; }
    CEXP iter_& operator++() NE {
      i = e[i].second;
      return *this;
    }
    CEXP bool operator!=(iter_ const& r) CNE { return i != r.i; }
  };

  vecu head;
  vecp<ET, u32> e;

 protected:
  using val_t = T;
  CEXPE eog_tag(u32 n) NE : base_t(n), head(n, -1_u32), e{} {}

 public:
  CEXP void add_arc(u32 u, auto&&... args) NE {
    base_t::add_arc(u, std::forward<decltype(args)>(args)...);
    e.emplace_back(ET(std::forward<decltype(args)>(args)...), head[u]);
    head[u] = u32(e.size() - 1);
  }
  CEXP u32 vsize() CNE { return (u32)head.size(); }
  CEXP void build() CNE {}
  CEXP void pop_startwith(u32 u) NE { base_t::del_arc(u, e[head[u]].first.to), head[u] = e[head[u]].second; }

  CEXP auto operator[](u32 u) CNE { return iter_{e, head[u]}; }
};
}  // namespace eog_impl_
template <class Et = void, class... Info>
using eog = graph_impl_::graph<eog_impl_::eog_tag<Et, Info...>>;

}  // namespace tifa_libs
