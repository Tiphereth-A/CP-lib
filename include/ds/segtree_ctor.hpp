#ifndef TIFALIBS_DS_SEGTREE_CTOR
#define TIFALIBS_DS_SEGTREE_CTOR

#include "segtree.hpp"

namespace tifa_libs::ds {
namespace segtree_ctor_impl_ {
template <class T>
struct P {
  T v;
  u32 l;
  friend CEXP P operator+(P CR l, P CR r) NE { return {l.v + r.v, l.l + r.l}; }
  friend std::ostream& operator<<(std::ostream& os, P CR p) NE { return os << p.v; }
};
template <class T>
CEXP void set_(T& x, cT_(T) y) NE { x = y; }
template <class T>
CEXP T add_op_(cT_(T) x, cT_(T) y) NE { return x + y; }
template <class T>
CEXP void add_(T& x, cT_(T) y) NE { x += y; }
template <class T>
CEXP T min_(cT_(T) x, cT_(T) y) NE { return min(x, y); }
template <class T>
CEXP T max_(cT_(T) x, cT_(T) y) NE { return max(x, y); }
template <class T>
CEXP void pset_(P<T>& x, cT_(T) y) NE { x.v = x.l * y; }
template <class T>
CEXP void padd_(P<T>& x, cT_(T) y) NE { x.v += x.l * y; }
template <class T>
CEXP auto segtl_addmax_ctor(cT_(T) ninf, spn<T> a) NE { return segtree<T, max_<T>, T, add_<T>, add_<T>>(ninf, T(0), a); }
template <class T>
CEXP auto segtl_addmin_ctor(cT_(T) inf, spn<T> a) NE { return segtree<T, min_<T>, T, add_<T>, add_<T>>(inf, T(0), a); }
template <class T>
CEXP auto segtl_addsum_ctor(vec<T> CR a) NE {
  vec<P<T>> b(a.size());
  flt_ (u32, i, 0, (u32)a.size()) b[i] = {a[i], 1};
  return segtree<P<T>, add_op_<P<T>>, T, padd_<T>, add_<T>>(P<T>{0, 0}, T(0), b);
}
template <class T>
CEXP auto segtl_setmax_ctor(cT_(T) ninf, spn<T> a) NE { return segtree<T, max_<T>, T, set_<T>, set_<T>>(ninf, ninf, a); }
template <class T>
CEXP auto segtl_setmin_ctor(cT_(T) inf, spn<T> a) NE { return segtree<T, min_<T>, T, set_<T>, set_<T>>(inf, inf, a); }
template <class T>
CEXP auto segtl_setsum_ctor(cT_(T) def_val, spn<T> a) NE {
  vec<P<T>> b(a.size());
  flt_ (u32, i, 0, (u32)a.size()) b[i] = {a[i], 1};
  return segtree<P<T>, add_op_<P<T>>, T, pset_<T>, set_<T>>(P<T>{0, 0}, def_val, b);
}
}  // namespace segtree_ctor_impl_

using segtree_ctor_impl_::segtl_addmax_ctor, segtree_ctor_impl_::segtl_addmin_ctor,
    segtree_ctor_impl_::segtl_addsum_ctor, segtree_ctor_impl_::segtl_setmax_ctor,
    segtree_ctor_impl_::segtl_setmin_ctor, segtree_ctor_impl_::segtl_setsum_ctor;

}  // namespace tifa_libs::ds

#endif