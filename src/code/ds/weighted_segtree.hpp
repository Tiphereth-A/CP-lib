#ifndef TIFALIBS_DS_LICHAO_WEIGHTED_SEGTREE
#define TIFALIBS_DS_LICHAO_WEIGHTED_SEGTREE

#include "../util/util.hpp"

namespace tifa_libs::ds {

class weighted_segtree {
  const usz n;
  vec<usz> t;

 public:
  explicit constexpr weighted_segtree(usz N) : n(N), t(N * 4) {}

  constexpr void ins(usz pos) { ins_(1, 0, n - 1, pos); }
  constexpr void del(usz pos) { del_(1, 0, n - 1, pos); }
  constexpr usz kth_min(usz k) { return kth_min_(1, 0, n - 1, k); }
  constexpr usz kth_max(usz k) { return kth_max_(1, 0, n - 1, k); }
  constexpr usz frequency(usz k) { return frequency_(1, 0, n - 1, k, k); }
  constexpr usz frequency(usz l, usz r) { return frequency_(1, 0, n - 1, l, r); }

 private:
  constexpr void ins_(usz x, usz l, usz r, usz pos) {
    if (l == r) return void(++t[x]);
    usz mid = l + (r - l) / 2;
    if (pos <= mid) ins_(x << 1, l, mid, pos);
    else ins_(x << 1 | 1, mid + 1, r, pos);
    t[x] = t[x << 1] + t[x << 1 | 1];
  }
  constexpr void del_(usz x, usz l, usz r, usz pos) {
    if (l == r) return void(--t[x]);
    usz mid = l + (r - l) / 2;
    if (pos <= mid) del_(x << 1, l, mid, pos);
    else del_(x << 1 | 1, mid + 1, r, pos);
    t[x] = t[x << 1] + t[x << 1 | 1];
  }
  constexpr usz kth_min_(usz x, usz l, usz r, usz k) const {
    if (l == r) return l;
    usz mid = l + (r - l) / 2;
    if (k <= t[x << 1]) return kth_min_(x << 1, l, mid, k);
    return kth_min_(x << 1 | 1, mid + 1, r, k - t[x << 1]);
  }
  constexpr usz kth_max_(usz x, usz l, usz r, usz k) const {
    if (l == r) return l;
    usz mid = l + (r - l) / 2;
    if (k <= t[x << 1 | 1]) return kth_max_(x << 1 | 1, mid + 1, r, k);
    return kth_max_(x << 1, l, mid, k - t[x << 1 | 1]);
  }
  constexpr usz frequency_(usz x, usz l, usz r, usz L, usz R) const {
    if (L <= l && R >= r) return t[x];
    usz mid = l + (r - l) / 2, ret = usz(0);
    if (L <= mid) ret = frequency_(x << 1, l, mid, L, R);
    if (R > mid) ret += frequency_(x << 1 | 1, mid + 1, r, L, R);
    return ret;
  }
};

}  // namespace tifa_libs::ds

#endif