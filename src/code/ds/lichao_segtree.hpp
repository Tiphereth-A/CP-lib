#ifndef TIFA_LIBS_DS_LICHAO_SEGTREE
#define TIFA_LIBS_DS_LICHAO_SEGTREE

#include <algorithm>
#include <climits>
#include <cstddef>

#include "../util/util.hpp"

namespace tifa_libs::ds {

template <class T, class F>
class lichao_segtree {
  struct seg {
    size_t id;
    T a, b, l, r;  // y = ax + b(where x in [l, r])
    T w(T x) { return a * x + b; }
  };
  F f;
  size_t sz;
  vec<T> lsh;
  vec<seg> t;
  bool pd(T a, T b) {//min: <=   max: >=
    return f(a, b) == a;
  }
  void add(size_t x, size_t l, size_t r, size_t L, size_t R, seg k) {
    size_t mid = l + (r - l) / 2;
    if (L <= l && R >= r) {
      if (!t[x].id) return void(t[x] = k);
      T tl = t[x].w(lsh[l]), tr = t[x].w(lsh[r]), kl = k.w(lsh[l]), kr = k.w(lsh[r]);
      if (pd(tl , kl) && pd(tr , kr)) return;
      if (!pd(tl , kl) && !pd(tr , kr)) return void(t[x] = k);
      double in = (t[x].b - k.b) / (k.a - t[x].a);
      if (pd(kl , tl))
        if (in <= lsh[mid])
          add(x << 1, l, mid, L, R, k);
        else
          add(x << 1 | 1, mid + 1, r, L, R, t[x]), t[x] = k;
      else if (in > lsh[mid])
        add(x << 1 | 1, mid + 1, r, L, R, k);
      else
        add(x << 1, l, mid, L, R, t[x]), t[x] = k;
      return;
    }
    if (L <= mid) add(x << 1, l, mid, L, R, k);
    if (R > mid) add(x << 1 | 1, mid + 1, r, L, R, k);
  }
  T query(size_t x, size_t l, size_t r, T pos) {
    T ret = t[x].id ? t[x].w(pos) : (pd(INT64_MIN, INT64_MAX) ? INT64_MAX : INT64_MIN);  // 怎么根据T来求最大（小）值
    if (l == r) return ret;
    size_t mid = l + (r - l) / 2;
    if (pos <= lsh[mid])
      return f(ret, query(x << 1, l, mid, pos));
    else
      return f(ret, query(x << 1 | 1, mid + 1, r, pos));
  }

 public:
  void add(T a, T b, T l, T r, size_t id = 1) {
    seg k = {id, a, b, l, r};
    l = std::lower_bound(lsh.begin(), lsh.end(), l) - lsh.begin();
    r = std::lower_bound(lsh.begin(), lsh.end(), r) - lsh.begin();
    add(1, 0, sz - 1, l, r, k);
  }
  T query(T pos) {
    return query(1, 0, sz - 1, pos);
  }
  explicit constexpr lichao_segtree(const vec<T>& LSH, F func) : lsh(LSH), t(LSH.size() * 4), f(func){ sz = lsh.size(); }
};
}  // namespace tifa_libs::ds

#endif