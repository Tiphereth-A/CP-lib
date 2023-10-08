#ifndef TIFA_LIBS_DS_SEGTREE_BEATS
#define TIFA_LIBS_DS_SEGTREE_BEATS

#include <cstddef>
#include <iostream>
#include <iterator>
#include <ostream>

#include "../util/util.hpp"

namespace tifa_libs::ds {

template <class T>
class segtree_beats {
  struct YYZ {
    T sum;
    T _min, secmin, cntmin;
    T _max, secmax, cntmax;
  };
  struct NFO {
    T add1, add2, add3;  // add sign of min, max and (no min or max)
  };
  size_t n;
  vec<YYZ> t;
  vec<NFO> sign;
  T INF;
  void pushup(size_t x) {
    t[x].sum = t[x << 1].sum + t[x << 1 | 1].sum;
    if (t[x << 1]._min == t[x << 1 | 1]._min) {
      t[x]._min = t[x << 1]._min;
      t[x].secmin = std::min(t[x << 1].secmin, t[x << 1 | 1].secmin);
      t[x].cntmin = t[x << 1].cntmin + t[x << 1 | 1].cntmin;
    } else if (t[x << 1]._min < t[x << 1 | 1]._min) {
      t[x]._min = t[x << 1]._min;
      t[x].secmin = std::min(t[x << 1].secmin, t[x << 1 | 1]._min);
      t[x].cntmin = t[x << 1].cntmin;
    } else {
      t[x]._min = t[x << 1 | 1]._min;
      t[x].secmin = std::min(t[x << 1]._min, t[x << 1 | 1].secmin);
      t[x].cntmin = t[x << 1 | 1].cntmin;
    }

    if (t[x << 1]._max == t[x << 1 | 1]._max) {
      t[x]._max = t[x << 1]._max;
      t[x].secmax = std::max(t[x << 1].secmax, t[x << 1 | 1].secmax);
      t[x].cntmax = t[x << 1].cntmax + t[x << 1 | 1].cntmax;
    } else if (t[x << 1]._max > t[x << 1 | 1]._max) {
      t[x]._max = t[x << 1]._max;
      t[x].secmax = std::max(t[x << 1].secmax, t[x << 1 | 1]._max);
      t[x].cntmax = t[x << 1].cntmax;
    } else {
      t[x]._max = t[x << 1 | 1]._max;
      t[x].secmax = std::max(t[x << 1]._max, t[x << 1 | 1].secmax);
      t[x].cntmax = t[x << 1 | 1].cntmax;
    }
  }
  void all_update(size_t x, size_t l, size_t r, T add1, T add2, T add3) {
    if (t[x]._min == t[x]._max) {
      if (add1 == add3)
        add1 = add2;
      else
        add2 = add1;
      t[x].sum += add1 * t[x].cntmin;
    } else
      t[x].sum += add1 * t[x].cntmin + add2 * t[x].cntmax + add3 * (T(r - l + 1) - t[x].cntmin - t[x].cntmax);
    if (t[x].secmin == t[x]._max)
      t[x].secmin += add2;
    else if (t[x].secmin != INF)
      t[x].secmin += add3;
    if (t[x].secmax == t[x]._min)
      t[x].secmax += add1;
    else if (t[x].secmax != -INF)
      t[x].secmax += add3;
    t[x]._min += add1, t[x]._max += add2;
    sign[x].add1 += add1, sign[x].add2 += add2, sign[x].add3 += add3;
  }
  void pushdown(size_t x, size_t l, size_t r) {
    if (sign[x].add1 || sign[x].add2 || sign[x].add2) {
      size_t mid = l + (r - l) / 2;
      T _min = std::min(t[x << 1]._min, t[x << 1 | 1]._min);
      T _max = std::max(t[x << 1]._max, t[x << 1 | 1]._max);
      all_update(x << 1, l, mid, t[x << 1]._min == _min ? sign[x].add1 : sign[x].add3,
                 t[x << 1]._max == _max ? sign[x].add2 : sign[x].add3, sign[x].add3);
      all_update(x << 1 | 1, mid + 1, r, t[x << 1 | 1]._min == _min ? sign[x].add1 : sign[x].add3,
                 t[x << 1 | 1]._max == _max ? sign[x].add2 : sign[x].add3, sign[x].add3);
      sign[x] = {0, 0, 0};
    }
  }
  void build(const vec<T>& a, size_t x, size_t l, size_t r) {
    if (l == r) {
      t[x].sum = t[x]._min = t[x]._max = a[l];
      t[x].secmin = INF, t[x].secmax = -INF;
      t[x].cntmin = t[x].cntmax = 1;
      return;
    }
    size_t mid = l + (r - l) / 2;
    build(a, x << 1, l, mid), build(a, x << 1 | 1, mid + 1, r);
    pushup(x);
  }

 public:
  void add(size_t x, size_t l, size_t r, size_t L, size_t R, T k) {
    if (L <= l && r <= R) {
      all_update(x, l, r, k, k, k);
      return;
    }
    pushdown(x, l, r);
    size_t mid = l + (r - l) / 2;
    if (L <= mid) add(x << 1, l, mid, L, R, k);
    if (R > mid) add(x << 1 | 1, mid + 1, r, L, R, k);
    pushup(x);
  }
  void chmax(size_t x, size_t l, size_t r, size_t L, size_t R, T k) {
    if (k <= t[x]._min) return;
    if (L <= l && r <= R && k < t[x].secmin) {
      all_update(x, l, r, k - t[x]._min, 0, 0);
      return;
    }
    pushdown(x, l, r);
    size_t mid = l + (r - l) / 2;
    if (L <= mid) chmax(x << 1, l, mid, L, R, k);
    if (R > mid) chmax(x << 1 | 1, mid + 1, r, L, R, k);
    pushup(x);
  }
  void chmin(size_t x, size_t l, size_t r, size_t L, size_t R, T k) {
    if (k >= t[x]._max) return;
    if (L <= l && r <= R && k > t[x].secmax) {
      all_update(x, l, r, 0, k - t[x]._max, 0);
      return;
    }
    pushdown(x, l, r);
    size_t mid = l + (r - l) / 2;
    if (L <= mid) chmin(x << 1, l, mid, L, R, k);
    if (R > mid) chmin(x << 1 | 1, mid + 1, r, L, R, k);
    pushup(x);
  }
  T querys(size_t x, size_t l, size_t r, size_t L, size_t R) {
    if (L <= l && r <= R) return t[x].sum;
    pushdown(x, l, r);
    size_t mid = l + (r - l) / 2;
    T ret = 0;
    if (L <= mid) ret = querys(x << 1, l, mid, L, R);
    if (R > mid) ret += querys(x << 1 | 1, mid + 1, r, L, R);
    return ret;
  }

  explicit constexpr segtree_beats(vec<T> const& a) : n(a.size()), t(a.size() * 4), sign(a.size() * 4), INF(std::numeric_limits<T>::max()) { build(a, 1, 0, n - 1); }
  explicit constexpr segtree_beats(std::size_t N) : n(N), t(N * 4), sign(N * 4), INF(std::numeric_limits<T>::max()) { build(vec<T>(n, 0), 1, 0, n - 1); }
};

}  // namespace tifa_libs::ds

#endif