#ifndef TIFALIBS_DS_SEGTREE
#define TIFALIBS_DS_SEGTREE

#include "../util/util.hpp"

namespace tifa_libs::ds {
namespace segtree_impl_ {
template <bool enable_tag, class T, auto op, class F, auto mapping, auto composition>
requires requires(T val, T new_val, F tag, F new_tag) {
  { op(val, new_val) } -> std::same_as<T>;
  { mapping(val, tag) } -> std::same_as<void>;
  { composition(tag, new_tag) } -> std::same_as<void>;
}
struct segtree {
  const T E;
  const F ID;

 private:
  u32 sz, lbn, n;
  vec<T> val;
  vec<F> tag;
  vecb vset;

 public:
  CEXP segtree(cT_(T) e, cT_(F) id) NE : E(e), ID(id), sz(0), lbn(0), n(0), val{}, tag{}, vset{} {}
  template <class V>
  CEXP segtree(cT_(T) e, cT_(F) id, V &&a) NE : segtree(e, id) { reset(std::forward<V>(a)); }
  CEXP segtree(cT_(T) e, cT_(F) id, u32 n) NE : segtree(e, id) { reset(vec<T>(n, e)); }

  template <class V>
  CEXP void reset(V &&a) NE {
    if (a.empty()) {
      sz = lbn = n = 0, val.clear(), tag.clear(), vset.clear();
      return;
    }
    sz = (u32)a.size(), lbn = (u32)std::bit_width(sz - 1), n = 1_u32 << lbn;
    if (!n) return;
    val = vec<T>(n * 2, E), copy(a, val.begin() + n);
    if CEXP (enable_tag) tag = vec<F>(n, ID), vset = vecb(n);
    for (u32 i = n - 1; i; --i) pushup(i);
  }
  //! 0-indexed, [l, r)
  CEXP void update(u32 l, u32 r, cT_(F) v) NE { upd_set<true>(l, r, v); }
  //! 0-indexed, [l, r)
  // set(3, 7, v): val[[3, 4), [4, 6), [6, 7)] <- v
  //! val[[4, 6)] != op(val[[3, 4)], val[[6, 7)])
  CEXP void set(u32 l, u32 r, cT_(F) v) NE { upd_set<false>(l, r, v); }
  //! 0-indexed, [l, r)
  CEXP T query(u32 l, u32 r) NE {
    if (assert(l <= r && r <= sz); l == r) return E;
    l += n, r += n;
    for (u32 i = lbn, zl = (u32)std::countr_zero(l), zr = (u32)std::countr_zero(r), ie = (u32)max(1, (i32)min(zl, zr)); i >= ie; --i) {
      if (zl < i) pushdown(l >> i);
      if (zr < i) pushdown((r - 1) >> i);
    }
    T ql = E, qr = E;
    while (l < r) {
      if (l & 1) ql = op(ql, val[l++]);
      if (r & 1) qr = op(val[--r], qr);
      l /= 2, r /= 2;
    }
    return op(ql, qr);
  }
  CEXP void update(u32 x, cT_(F) v) NE { upd_set<true>(x, v); }
  CEXP void set(u32 x, cT_(T) v) NE { upd_set<false>(x, v); }
  CEXP T query(u32 x) NE {
    assert(x < sz), x += n;
    for (u32 i = lbn; i; --i) pushdown(x >> i);
    return val[x];
  }
  template <class G>
  requires requires(G check, T val) {
    { check(val) } -> std::same_as<bool>;
  }
  CEXP u32 max_right(u32 l, G &&chk) NE {
    if (assert(l <= sz && chk(ID)); l == n) return n;
    l += n;
    for (u32 i = lbn; i; --i) pushdown(l >> i);
    T _ = E;
    do {
      if (!chk(op(_, val[l >>= std::countr_zero(l)]))) {
        while (l < n)
          if (pushdown(l), l *= 2; chk(op(_, val[l]))) _ = op(_, val[l++]);
        return l - n;
      }
      _ = op(_, val[l++]);
    } while (!std::has_single_bit(l));
    return sz;
  }
  template <class G>
  requires requires(G check, T val) {
    { check(val) } -> std::same_as<bool>;
  }
  CEXP u32 min_left(u32 r, G chk) NE {
    if (assert(r <= sz && chk(ID)); !r) return 0;
    r += n;
    for (u32 i = lbn; i; --i) pushdown((r - 1) >> i);
    T _ = E;
    do {
      if (!(--r, r >>= std::countr_one(r))) r = 1;
      if (!chk(op(val[r], _))) {
        while (r < n)
          if (pushdown(r), r = r * 2 + 1; chk(op(val[r], _))) _ = op(val[r--], _);
        return r + 1 - n;
      }
      _ = op(val[r], _);
    } while (!std::has_single_bit(r));
    return 0;
  }

 private:
  CEXP void compose(F &a, cT_(F) b) CNE {
    if (a == ID) a = b;
    else composition(a, b);
  }
  CEXP void pushup(u32 x) NE { val[x] = op(val[x * 2], val[x * 2 + 1]); }
  template <bool upd>
  CEXP void apply(u32 x, std::conditional_t<upd, cT_(F), cT_(T)> f) NE {
    if CEXP (upd) {
      if (f == ID) return;
      if CEXP (mapping(val[x], f); enable_tag)
        if (x < n) compose(tag[x], f);
    } else if CEXP (val[x] = f; enable_tag)
      if (x < n) tag[x] = ID, vset[x] = 1;
  }
  CEXP void pushdown(u32 x) NE {
    if CEXP (enable_tag) {
      if (vset[x]) {
        val[x * 2] = val[x * 2 + 1] = val[x];
        if (x * 2 < n) tag[x * 2] = tag[x * 2 + 1] = ID, vset[x * 2] = vset[x * 2 + 1] = 1;
        vset[x] = 0;
      } else if (tag[x] != ID) {
        mapping(val[x * 2], tag[x]), mapping(val[x * 2 + 1], tag[x]);
        if (x * 2 < n) compose(tag[x * 2], tag[x]), compose(tag[x * 2 + 1], tag[x]);
        tag[x] = ID;
      }
    }
  }
  template <bool upd>
  CEXP void upd_set(u32 l, u32 r, std::conditional_t<upd, cT_(F), cT_(T)> v) NE {
    if (assert(l <= r && r <= sz); l == r) return;
    l += n, r += n;
    u32 zl = (u32)std::countr_zero(l), zr = (u32)std::countr_zero(r), zm = min(zl, zr);
    for (u32 i = lbn, ie = (u32)max(1, (i32)zm); i >= ie; --i) {
      if (zl < i) pushdown(l >> i);
      if (zr < i) pushdown((r - 1) >> i);
    }
    u32 l2 = l, r2 = r;
    while (l2 < r2) {
      if (l2 & 1) apply<upd>(l2++, v);
      if (r2 & 1) apply<upd>(--r2, v);
      l2 /= 2, r2 /= 2;
    }
    flt_ (u32, i, zm + 1, lbn + 1) {
      if (zl < i) pushup(l >> i);
      if (zr < i) pushup((r - 1) >> i);
    }
  }
  template <bool upd>
  CEXP void upd_set(u32 x, std::conditional_t<upd, cT_(F), cT_(T)> v) NE {
    assert(x < sz), x += n;
    for (u32 i = lbn; i; --i) pushdown(x >> i);
    if CEXP (upd) mapping(val[x], v);
    else val[x] = v;
    flt_ (u32, i, 1, lbn + 1) pushup(x >> i);
  }
};
}  // namespace segtree_impl_

template <class T, auto op, class F, auto mapping, auto composition>
using segtree = segtree_impl_::segtree<true, T, op, F, mapping, composition>;
template <class T, auto op, auto mapping>
class segtree_notag : public segtree_impl_::segtree<false, T, op, T, mapping, mapping> {
  using base = segtree_impl_::segtree<false, T, op, T, mapping, mapping>;

 public:
  CEXPE segtree_notag(cT_(T) e) NE : base(e, e) {}
  template <class V>
  CEXP segtree_notag(cT_(T) e, V &&a) NE : base(e, e, std::forward<V>(a)) {}
  CEXP segtree_notag(cT_(T) e, u32 n) NE : base(e, e, n) {}
};

}  // namespace tifa_libs::ds

#endif