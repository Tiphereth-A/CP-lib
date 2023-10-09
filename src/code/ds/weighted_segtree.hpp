#ifndef TIFA_LIBS_DS_LICHAO_WEIGHTED_SEGTREE
#define TIFA_LIBS_DS_LICHAO_WEIGHTED_SEGTREE

#include "../util/util.hpp"

namespace tifa_libs::ds {

class weighted_segtree {
  size_t n;
  vec<size_t> t;

 public:
  void add(size_t x, size_t l, size_t r, size_t pos) {
    if (l == r) t[x] += 1;
    size_t mid = l + (r - l) / 2;
    if (pos <= mid) add(x << 1, l, mid, pos);
    else add(x << 1 | 1, mid + 1, r, pos);
    t[x] = t[x << 1] + t[x << 1 | 1];
  }
  size_t kth_smallest(size_t x, size_t l, size_t r, size_t k) {
    if (l == r) return l;
    size_t mid = l + (r - l) / 2;
    if (k <= t[x << 1]) return kth_smallest(x << 1, l, mid, k);
    return kth_smallest(x << 1 | 1, mid + 1, r, k - t[x << 1]);
  }
  size_t kth_biggest(size_t x, size_t l, size_t r, size_t k) {
    if (l == r) return l;
    size_t mid = l + (r - l) / 2;
    if (k <= t[x << 1 | 1]) return kth_smallest(x << 1 | 1, mid + 1, r, k);
    return kth_smallest(x << 1, l, mid, k - t[x << 1 | 1]);
  }
  size_t frequency(size_t x, size_t l, size_t r, size_t k) {
    if (l == r) return t[x];
    else {
      size_t mid = (l + r) >> 1;
      if (k <= mid) return frequency(x << 1, l, mid, k);
      return frequency(x << 1 | 1, mid + 1, r, k);
    }
  }
  size_t frequency(size_t x, size_t l, size_t r, size_t L, size_t R) {
    if (l == r) return t[x];
    else {
      size_t mid = (l + r) >> 1, ret = size_t(0);
      if (L <= mid) ret = frequency(x << 1, l, mid, L, R);
      if (R > mid) ret += frequency(x << 1 | 1, mid + 1, r, L, R);
      return ret;
    }
  }
  weighted_segtree(vec<size_t> const &a, const size_t &N) : n(N), t(N * 4) {
    for (auto x : a) add(1, 0, n - 1, x);
  }
};
}  // namespace tifa_libs::ds

#endif