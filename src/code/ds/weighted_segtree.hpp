#ifndef TIFA_LIBS_DS_LICHAO_WEIGHTED_SEGTREE
#define TIFA_LIBS_DS_LICHAO_WEIGHTED_SEGTREE

#include "../util/util.hpp"

namespace tifa_libs::ds {

class weighted_segtree {
  const size_t n;
  vec<size_t> t;

  void ins_(size_t x, size_t l, size_t r, size_t pos) {
    if (l == r) return void(++t[x]);
    size_t mid = l + (r - l) / 2;
    if (pos <= mid) ins_(x << 1, l, mid, pos);
    else ins_(x << 1 | 1, mid + 1, r, pos);
    t[x] = t[x << 1] + t[x << 1 | 1];
  }
  void del_(size_t x, size_t l, size_t r, size_t pos) {
    if (l == r) return void(--t[x]);
    size_t mid = l + (r - l) / 2;
    if (pos <= mid) del_(x << 1, l, mid, pos);
    else del_(x << 1 | 1, mid + 1, r, pos);
    t[x] = t[x << 1] + t[x << 1 | 1];
  }
  size_t kth_min_(size_t x, size_t l, size_t r, size_t k) const {
    if (l == r) return l;
    size_t mid = l + (r - l) / 2;
    if (k <= t[x << 1]) return kth_min_(x << 1, l, mid, k);
    return kth_min_(x << 1 | 1, mid + 1, r, k - t[x << 1]);
  }
  size_t kth_max_(size_t x, size_t l, size_t r, size_t k) const {
    if (l == r) return l;
    size_t mid = l + (r - l) / 2;
    if (k <= t[x << 1 | 1]) return kth_max_(x << 1 | 1, mid + 1, r, k);
    return kth_max_(x << 1, l, mid, k - t[x << 1 | 1]);
  }
  size_t frequency_(size_t x, size_t l, size_t r, size_t k) const {
    if (l == r) return t[x];
    else {
      size_t mid = l + (r - l) / 2;
      if (k <= mid) return frequency_(x << 1, l, mid, k);
      return frequency_(x << 1 | 1, mid + 1, r, k);
    }
  }
  size_t frequency_(size_t x, size_t l, size_t r, size_t L, size_t R) const {
    if (l == r) return t[x];
    else {
      size_t mid = l + (r - l) / 2, ret = size_t(0);
      if (L <= mid) ret = frequency_(x << 1, l, mid, L, R);
      if (R > mid) ret += frequency_(x << 1 | 1, mid + 1, r, L, R);
      return ret;
    }
  }

 public:
  explicit weighted_segtree(size_t N) : n(N), t(N * 4) {}

  void ins(size_t pos) { ins_(1, 0, n - 1, pos); }
  void del(size_t pos) { del_(1, 0, n - 1, pos); }
  size_t kth_min(size_t k) { return kth_min_(1, 0, n - 1, k); }
  size_t kth_max(size_t k) { return kth_max_(1, 0, n - 1, k); }
  size_t frequency(size_t k) { return frequency_(1, 0, n - 1, k); }
  size_t frequency(size_t l, size_t r) { return frequency_(1, 0, n - 1, l, r); }
};
}  // namespace tifa_libs::ds

#endif