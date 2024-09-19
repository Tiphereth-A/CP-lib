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
  CEXP E() {}
  CEXP E(u32 v, cT_(T) c) : to(v), cost(c) {}
  CEXP operator u32() const { return to; }
};
template <class T>
struct E<T, true> {
  u32 to;
  CEXP E() {}
  CEXP E(u32 v) : to(v) {}
  CEXP operator u32() const { return to; }
};
}  // namespace alists_impl_

template <class T = void, bool with_deg = false>
class alists {
  template <class I>
  struct Es {
    I b, e;
    CEXP I begin() const { return b; }
    CEXP I end() const { return e; }
    CEXP u32 size() const { return u32(e - b); }
    CEXP auto&& operator[](u32 i) const { return b[i]; }
  };
  using ET = alists_impl_::E<T>;
  vecu h;
  vecp<u32, ET> b;
  vec<ET> e;

 public:
  using w_t = T;
  u32 cnt_arc;
  vecu deg_in, deg_out;
  CEXP alists(u32 n) : h(n + 1), b(), e(), cnt_arc(0), deg_in(0), deg_out(0) {
    if CEXP (with_deg) deg_in.resize(n), deg_out.resize(n);
  }
  CEXP alists(u32 n, u32 m) : alists(n) { b.reserve(m); }
  //! DO NOT call this after called %build
  template <class... Ts>
  CEXP void add_arc(u32 u, Ts&&... args) { b.emplace_back(u, ET{std::forward<Ts>(args)...}), ++h[u]; }
  CEXP void build() {
    if (cnt_arc) return;
    std::partial_sum(h.begin(), h.end(), h.begin());
    for (e.resize(cnt_arc = (u32)b.size()); auto CR[u, e] : b) e[--h[u]] = e;
    if CEXP (with_deg)
      for (auto CR[u, e] : b) ++deg_out[u], ++deg_in[e.to];
  }
  CEXP u32 size() const { return h.size() - 1; }
  CEXP Es<TPN vec<ET>::iterator> operator[](u32 u) { return {e.begin() + h[u], e.begin() + h[u + 1]}; }
  CEXP const Es<TPN vec<ET>::const_iterator> operator[](u32 u) const { return {e.begin() + h[u], e.begin() + h[u + 1]}; }
};

}  // namespace tifa_libs::graph

#endif