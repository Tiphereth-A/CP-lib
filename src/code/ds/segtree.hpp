#ifndef TIFA_LIBS_DS_SEGTREE
#define TIFA_LIBS_DS_SEGTREE

#include "../util/util.hpp"

namespace tifa_libs::ds {

// template <class T, T (*op)(T, T), T (*e)(), class F, T (*mapping)(F, T), F (*composition)(F, F), F (*id)()>
template <class T, auto op, auto e, class F, auto mapping, auto composition, auto id>
class segtree {
  vec<T> t;
  vec<F> sign;
  size_t n;
  void pushup(size_t x) { t[x] = op(t[x << 1], t[x << 1 | 1]); }
  void all_update(size_t x, F f) { t[x] = mapping(f, t[x]), sign[x] = composition(f, sign[x]); }
  void pushdown(size_t x) { all_update(x << 1, sign[x]), all_update(x << 1 | 1, sign[x]), sign[x] = id(); }
  void build(vec<T> const &a, size_t x, size_t l, size_t r) {
    sign[x] = id();
    if (l == r) return void(t[x] = a[l]);
    size_t mid = l + (r - l) / 2;
    build(a, x << 1, l, mid), build(a, x << 1 | 1, mid + 1, r);
    pushup(x);
  }

 public:
  void update(size_t x, size_t l, size_t r, size_t L, size_t R, F f) {
    if (L <= l && R >= r) return void(all_update(x, f));
    pushdown(x);
    size_t mid = l + (r - l) / 2;
    if (L <= mid) update(x << 1, l, mid, L, R, f);
    if (R > mid) update(x << 1 | 1, mid + 1, r, L, R, f);
    pushup(x);
  }
  T query(size_t x, size_t l, size_t r, size_t L, size_t R) {
    if (L <= l && R >= r) return t[x];
    pushdown(x);
    size_t mid = l + (r - l) / 2;
    T ret = e();
    if (L <= mid) ret = op(ret, query(x << 1, l, mid, L, R));
    if (R > mid) ret = op(ret, query(x << 1 | 1, mid + 1, r, L, R));
    return ret;
  }
  T query(size_t x, size_t l, size_t r, size_t pos) { return query(x, l, r, pos, pos); }
  explicit constexpr segtree(vec<T> const &a) : t(a.size() * 4), sign(a.size() * 4), n(a.size()) { build(a, 1, 0, n - 1); }
  explicit constexpr segtree(std::size_t N) : t(N * 4), sign(N * 4), n(N) { build(vec<T>(n, e()), 1, 0, n - 1); }
};

}  // namespace tifa_libs::ds

#endif