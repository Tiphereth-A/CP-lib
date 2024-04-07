#ifndef TIFALIBS_DS_SEGTREE
#define TIFALIBS_DS_SEGTREE

#include "../util/util.hpp"

namespace tifa_libs::ds {
namespace segtree_impl_ {
template <bool use_tag, class T, auto op, auto e, class F, auto mapping, auto composition, auto id>
requires requires(T val, T val_l, T val_r, F tag) {
  { e() } -> std::same_as<T>;
  { op(val_l, val_r) } -> std::same_as<T>;
  { id() } -> std::same_as<F>;
  { mapping(tag, val) } -> std::same_as<T>;
}
class segtree {
  vec<T> t;
  vec<F> sign;
  vecb set_sign;
  u32 n;

 public:
  explicit constexpr segtree(vec<T> const &a) : t(a.size() * 4), sign(), set_sign(), n((u32)a.size()) {
    if constexpr (use_tag) sign.resize(t.size()), set_sign.resize(t.size());
    build(a, 1, 0, n - 1);
  }
  explicit constexpr segtree(u32 N = 0) : t(N * 4), sign(), set_sign(), n(N) {
    if constexpr (use_tag) sign.resize(t.size()), set_sign.resize(t.size());
    if (n) build(vec<T>(n, e()), 1, 0, n - 1);
  }

  constexpr void update(u32 L, u32 R, F f) { update(1, 0, n - 1, L, R, f); }
  constexpr void update(u32 pos, F f) { update(1, 0, n - 1, pos, pos, f); }
  constexpr void set(u32 L, u32 R, T f) { set(1, 0, n - 1, L, R, f); }
  constexpr void set(u32 pos, T f) { set(1, 0, n - 1, pos, pos, f); }
  constexpr T query(u32 L, u32 R) { return query(1, 0, n - 1, L, R); }
  constexpr T query(u32 pos) { return query(1, 0, n - 1, pos, pos); }

 private:
  constexpr void pushup(u32 x) { t[x] = op(t[x * 2], t[x * 2 + 1]); }
  constexpr void all_update(u32 x, F f) {
    t[x] = mapping(f, t[x]);
    if constexpr (use_tag) sign[x] = composition(f, sign[x]);
  }
  constexpr void all_set(u32 x, T f) {
    t[x] = f;
    if constexpr (use_tag) sign[x] = id(), set_sign[x] = 1;
  }
  constexpr void pushdown(u32 x) {
    if constexpr (use_tag) {
      if (set_sign[x]) all_set(x * 2, t[x]), all_set(x * 2 + 1, t[x]), set_sign[x] = 0;
      else all_update(x * 2, sign[x]), all_update(x * 2 + 1, sign[x]), sign[x] = id();
    }
  }
  constexpr void build(vec<T> const &a, u32 x, u32 l, u32 r) {
    if constexpr (use_tag) sign[x] = id();
    if (l == r) return void(t[x] = a[l]);
    u32 mid = l + (r - l) / 2;
    build(a, x * 2, l, mid), build(a, x * 2 + 1, mid + 1, r);
    pushup(x);
  }
  constexpr void update(u32 x, u32 l, u32 r, u32 L, u32 R, F f) {
    assert(R >= l && L <= r);
    if (L <= l && R >= r) return void(all_update(x, f));
    pushdown(x);
    u32 mid = l + (r - l) / 2;
    if (L <= mid) update(x * 2, l, mid, L, R, f);
    if (R > mid) update(x * 2 + 1, mid + 1, r, L, R, f);
    pushup(x);
  }
  constexpr void set(u32 x, u32 l, u32 r, u32 L, u32 R, T f) {
    assert(R >= l && L <= r);
    if (L <= l && R >= r) return void(all_set(x, f));
    pushdown(x);
    u32 mid = l + (r - l) / 2;
    if (L <= mid) set(x * 2, l, mid, L, R, f);
    if (R > mid) set(x * 2 + 1, mid + 1, r, L, R, f);
    pushup(x);
  }
  constexpr T query(u32 x, u32 l, u32 r, u32 L, u32 R) {
    assert(R >= l && L <= r);
    if (L <= l && R >= r) return t[x];
    pushdown(x);
    u32 mid = l + (r - l) / 2;
    T ret = e();
    if (L <= mid) ret = op(ret, query(x * 2, l, mid, L, R));
    if (R > mid) ret = op(ret, query(x * 2 + 1, mid + 1, r, L, R));
    return ret;
  }
};
}  // namespace segtree_impl_

template <class T, auto op, auto e, class F, auto mapping, auto composition, auto id>
requires requires(F tag_l, F tag_r) {
  { composition(tag_l, tag_r) } -> std::same_as<F>;
}
using segtree = segtree_impl_::segtree<true, T, op, e, F, mapping, composition, id>;
template <class T, auto op, auto e>
using segtree_notag = segtree_impl_::segtree<false, T, op, e, T, op, op, e>;

}  // namespace tifa_libs::ds

#endif