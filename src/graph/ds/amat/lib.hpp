#pragma once

#include "../graph_c/lib.hpp"

namespace tifa_libs {
namespace amat_impl_ {
template <class T, class... Info>
class amat_tag : public graph_info_impl_::graph_tag_base<Info...> {
  using base_t = graph_info_impl_::graph_tag_base<Info...>;
  using ET = std::conditional_t<std::is_void_v<T>, u32, T>;
  struct iter_ {
    using iter_t = vec<ET>::const_iterator;
    iter_t it, bgn, ed;
    CEXP iter_(iter_t begin, iter_t end) NE : it(begin), bgn(begin), ed(end) { nomalize(), bgn = it; }

    CEXP auto begin() CNE { return iter_{bgn, ed}; }
    CEXP auto end() CNE { return iter_{ed, ed}; }

    CEXP auto operator*() CNE { return *it; }
    CEXP iter_& operator++() NE {
      ++it, nomalize();
      return *this;
    }
    CEXP bool operator!=(iter_ const& r) CNE { return it != r.it; }

   private:
    CEXP void nomalize() NE {
      while (it != ed && *it == ET{}) ++it;
    }
  };
  vvec<ET> g;

 protected:
  using val_t = T;
  CEXPE amat_tag(u32 n, ET const null = {}) NE : base_t(n), g(n, vec<ET>(n, null)) {
    flt_ (u32, i, 0, n) g[i][i] = ET{};
  }

 public:
  CEXP void build() CNE {}
  CEXP void add_arc(u32 u, u32 v, cT_(ET) w = 1) NE { g[u][v] = w, base_t::add_arc(u, v); }
  CEXP u32 vsize() CNE { return (u32)g.size(); }

  CEXP auto CR operator[](u32 u) CNE { return iter_{g[u].begin(), g[u].end()}; }
  CEXP auto val(u32 u, u32 v) CNE { return g[u][v]; }
  CEXP void set_val(u32 u, u32 v, cT_(ET) w) NE { g[u][v] = w; }
};
}  // namespace amat_impl_
template <class Et = void, class... Info>
using amat = graph_impl_::graph<amat_impl_::amat_tag<Et, Info...>>;

}  // namespace tifa_libs
