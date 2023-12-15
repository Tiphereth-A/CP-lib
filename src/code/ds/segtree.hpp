#ifndef TIFALIBS_DS_SEGTREE
#define TIFALIBS_DS_SEGTREE

#include "../util/util.hpp"

namespace tifa_libs::ds {

// template <class T, T (*op)(T, T), T (*e)(), class F, T (*mapping)(F, T), F (*composition)(F, F), F (*id)()>
template <class T, auto op, auto e, class F, auto mapping, auto composition, auto id>
class segtree {
  vec<T> t;
  vec<F> sign;
  vec<bool> set_sign;
  usz n;

 public:
  explicit constexpr segtree(vec<T> const &a) : t(a.size() * 4), sign(a.size() * 4), set_sign(a.size() * 4), n(a.size()) { build(a, 1, 0, n - 1); }
  explicit constexpr segtree(usz N = 0) : t(N * 4), sign(N * 4), set_sign(N * 4), n(N) {
    if (n) build(vec<T>(n, e()), 1, 0, n - 1);
  }

  constexpr void update(usz L, usz R, F f) { update(1, 0, n - 1, L, R, f); }
  constexpr void update(usz pos, F f) { update(1, 0, n - 1, pos, pos, f); }
  constexpr void set(usz L, usz R, T f) { set(1, 0, n - 1, L, R, f); }
  constexpr void set(usz pos, T f) { set(1, 0, n - 1, pos, pos, f); }
  constexpr T query(usz L, usz R) { return query(1, 0, n - 1, L, R); }
  constexpr T query(usz pos) { return query(1, 0, n - 1, pos, pos); }

 private:
  constexpr void pushup(usz x) { t[x] = op(t[x << 1], t[x << 1 | 1]); }
  constexpr void all_update(usz x, F f) { t[x] = mapping(f, t[x]), sign[x] = composition(f, sign[x]); }
  constexpr void all_set(usz x, T f) { t[x] = f, sign[x] = id(), set_sign[x] = 1; }
  constexpr void pushdown(usz x) {
    if (set_sign[x]) all_set(x << 1, t[x]), all_set(x << 1 | 1, t[x]), set_sign[x] = 0;
    else all_update(x << 1, sign[x]), all_update(x << 1 | 1, sign[x]), sign[x] = id();
  }
  constexpr void build(vec<T> const &a, usz x, usz l, usz r) {
    sign[x] = id();
    if (l == r) return void(t[x] = a[l]);
    usz mid = l + (r - l) / 2;
    build(a, x << 1, l, mid), build(a, x << 1 | 1, mid + 1, r);
    pushup(x);
  }
  constexpr void update(usz x, usz l, usz r, usz L, usz R, F f) {
    assert(R >= l && L <= r);
    if (L <= l && R >= r) return void(all_update(x, f));
    pushdown(x);
    usz mid = l + (r - l) / 2;
    if (L <= mid) update(x << 1, l, mid, L, R, f);
    if (R > mid) update(x << 1 | 1, mid + 1, r, L, R, f);
    pushup(x);
  }
  constexpr void set(usz x, usz l, usz r, usz L, usz R, T f) {
    assert(R >= l && L <= r);
    if (L <= l && R >= r) return void(all_set(x, f));
    pushdown(x);
    usz mid = l + (r - l) / 2;
    if (L <= mid) set(x << 1, l, mid, L, R, f);
    if (R > mid) set(x << 1 | 1, mid + 1, r, L, R, f);
    pushup(x);
  }
  constexpr T query(usz x, usz l, usz r, usz L, usz R) {
    assert(R >= l && L <= r);
    if (L <= l && R >= r) return t[x];
    pushdown(x);
    usz mid = l + (r - l) / 2;
    T ret = e();
    if (L <= mid) ret = op(ret, query(x << 1, l, mid, L, R));
    if (R > mid) ret = op(ret, query(x << 1 | 1, mid + 1, r, L, R));
    return ret;
  }
};

}  // namespace tifa_libs::ds

#endif