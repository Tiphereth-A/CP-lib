#ifndef TIFALIBS_DS_SEGTREE_CTOR
#define TIFALIBS_DS_SEGTREE_CTOR

#include "segtree.hpp"

namespace tifa_libs::ds {
namespace segtree_ctor_impl_ {
template <class T>
struct P {
  T v;
  u32 l;
  friend CEXP P operator+(P CR l, P CR r) { return {l.v + r.v, l.l + r.l}; }
  friend std::ostream& operator<<(std::ostream& os, P CR p) { return os << p.v; }
};
template <class T>
CEXP T set_(cT_(T), cT_(T) y) { return y; }
template <class T>
CEXP T add_(cT_(T) x, cT_(T) y) { return x + y; }
template <class T>
CEXP T min_(cT_(T) x, cT_(T) y) { return min(x, y); }
template <class T>
CEXP T max_(cT_(T) x, cT_(T) y) { return max(x, y); }
template <class T>
CEXP P<T> pset_(P<T> CR x, cT_(T) y) { return {x.l * y, x.l}; }
template <class T>
CEXP P<T> padd_(P<T> CR x, cT_(T) y) { return {x.v + x.l * y, x.l}; }
template <class T>
CEXP T e_() { return T(0); }
template <class T, T val>
CEXP T v_() { return val; }
template <class T>
CEXP P<T> pe_() { return {0, 0}; }
template <class T, T NINF>
CEXP auto segtl_addmax_ctor(vec<T> CR a) { return segtree<T, max_<T>, v_<T, NINF>, T, add_<T>, add_<T>, e_<T>>(a); }
template <class T, T INF>
CEXP auto segtl_addmin_ctor(vec<T> CR a) { return segtree<T, min_<T>, v_<T, INF>, T, add_<T>, add_<T>, e_<T>>(a); }
template <class T>
CEXP auto segtl_addsum_ctor(vec<T> CR a) {
  vec<P<T>> b(a.size());
  flt_ (u32, i, 0, (u32)a.size()) b[i] = {a[i], 1};
  return segtree<P<T>, add_<P<T>>, pe_<T>, T, padd_<T>, add_<T>, e_<T>>(b);
}
template <class T, T NINF>
CEXP auto segtl_setmax_ctor(vec<T> CR a) { return segtree<T, max_<T>, v_<T, NINF>, T, set_<T>, set_<T>, v_<T, NINF>>(a); }
template <class T, T INF>
CEXP auto segtl_setmin_ctor(vec<T> CR a) { return segtree<T, min_<T>, v_<T, INF>, T, set_<T>, set_<T>, v_<T, INF>>(a); }
template <class T, T DEF_VAL>
CEXP auto segtl_setsum_ctor(vec<T> CR a) {
  vec<P<T>> b(a.size());
  flt_ (u32, i, 0, (u32)a.size()) b[i] = {a[i], 1};
  return segtree<P<T>, add_<P<T>>, pe_<T>, T, pset_<T>, set_<T>, v_<T, DEF_VAL>>(b);
}
}  // namespace segtree_ctor_impl_

using segtree_ctor_impl_::segtl_addmax_ctor, segtree_ctor_impl_::segtl_addmin_ctor, segtree_ctor_impl_::segtl_addsum_ctor;
using segtree_ctor_impl_::segtl_setmax_ctor, segtree_ctor_impl_::segtl_setmin_ctor, segtree_ctor_impl_::segtl_setsum_ctor;

}  // namespace tifa_libs::ds

#endif