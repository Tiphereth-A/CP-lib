#ifndef TIFA_LIBS_DS_SEGTREE
#define TIFA_LIBS_DS_SEGTREE

#include "../util/util.hpp"


namespace tifa_libs::ds {

template <class T, class F>
class segtree {
  struct YYZ {
    T w, sign, sign1, _min, _max;
  };
  vec<YYZ> t;
  void pushup(size_t x) {
    t[x].w = t[x << 1].w + t[x << 1 | 1].w;
    t[x]._min = std::min(t[x << 1]._min, t[x << 1 | 1]._min);
    t[x]._max = std::max(t[x << 1]._max, t[x << 1 | 1]._max);
  }
  void build(vec<T> const &a, size_t x, size_t l, size_t r) {
    t[x].sign1 = 1;
    if (l == r) return void(t[x].w = a[l]);
    size_t mid = l + (r - l) / 2;
    build(a, x << 1, l, mid), build(a, x << 1 | 1, mid + 1, r);
    pushup(x);
  }
  void pushdown(size_t x, size_t l, size_t r) {  // sign1(*) must be pushdowned before sign(+)
    if (t[x].sign1 != 1) {
      t[x << 1].w *= t[x].sign1;
      t[x << 1].sign *= t[x].sign1, t[x << 1].sign1 *= t[x].sign1;
      t[x << 1]._min *= t[x].sign1, t[x << 1]._max *= t[x].sign1;
      t[x << 1 | 1].w *= t[x].sign1;
      t[x << 1 | 1].sign *= t[x].sign1, t[x << 1 | 1].sign1 *= t[x].sign1;
      t[x << 1 | 1]._min *= t[x].sign1, t[x << 1 | 1]._max *= t[x].sign1;
      t[x].sign1 = 1;
    }
    if (t[x].sign) {
      size_t mid = l + (r - l) / 2;
      t[x << 1].w += i64(mid - l + 1) * t[x].sign, t[x << 1].sign += t[x].sign;
      t[x << 1]._min += t[x].sign, t[x << 1]._max += t[x].sign;
      t[x << 1 | 1].w += i64(r - mid) * t[x].sign, t[x << 1 | 1].sign += t[x].sign;
      t[x << 1 | 1]._min += t[x].sign, t[x << 1 | 1]._max += t[x].sign;
      t[x].sign = 0;
    }
  }

 public:
  void add(size_t x, size_t l, size_t r, size_t L, size_t R, T k) {
    if (L <= l && R >= r) {
      t[x].w += i64(r - l + 1) * k, t[x].sign += k;
      t[x]._min += k, t[x]._max += k;
      return;
    }
    pushdown(x, l, r);
    size_t mid = l + (r - l) / 2;
    if (L <= mid) add(x << 1, l, mid, L, R, k);
    if (R > mid) add(x << 1 | 1, mid + 1, r, L, R, k);
    pushup(x);
  }
  void mul(size_t x, size_t l, size_t r, size_t L, size_t R, T k) {
    if (L <= l && R >= r) {
      t[x].w *= k;
      t[x].sign *= k, t[x].sign1 *= k;
      t[x]._min *= k, t[x]._max *= k;
      return;
    }
    pushdown(x, l, r);
    size_t mid = l + (r - l) / 2;
    if (L <= mid) mul(x << 1, l, mid, L, R, k);
    if (R > mid) mul(x << 1 | 1, mid + 1, r, L, R, k);
    pushup(x);
  }
  T querys(size_t x, size_t l, size_t r, size_t L, size_t R) {
    if (L <= l && R >= r) return t[x].w;
    pushdown(x, l, r);
    size_t mid = l + (r - l) / 2;
    T ret = 0;
    if (L <= mid) ret = querys(x << 1, l, mid, L, R);
    if (R > mid) ret += querys(x << 1 | 1, mid + 1, r, L, R);
    return ret;
  }
  T querym(size_t x, size_t l, size_t r, size_t L, size_t R, F f) {
    if (L <= l && R >= r) return f(t[x]._min, t[x]._max);
    pushdown(x, l, r);
    size_t mid = l + (r - l) / 2;
    if (L > mid) return querym(x << 1 | 1, mid + 1, r, L, R, f);
    if (R <= mid) return querym(x << 1, l, mid, L, R, f);
    return f(querym(x << 1, l, mid, L, R, f), querym(x << 1 | 1, mid + 1, r, L, R, f));
  }
  explicit constexpr segtree(vec<T> const &a) : t(a.size() * 4) { build(a, 1, 0, a.size() - 1); }
};

}  // namespace tifa_libs::ds

#endif