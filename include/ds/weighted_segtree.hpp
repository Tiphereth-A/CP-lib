#ifndef TIFALIBS_DS_LICHAO_WEIGHTED_SEGTREE
#define TIFALIBS_DS_LICHAO_WEIGHTED_SEGTREE

#include "../util/alias_others.hpp"

namespace tifa_libs::ds {

class weighted_segtree {
  const u32 n;
  vecu t;

 public:
  CEXPE weighted_segtree(u32 N) NE : n(N), t(N * 4) {}

  CEXP void ins(u32 pos) NE { ins_(1, 0, n - 1, pos); }
  CEXP void del(u32 pos) NE { del_(1, 0, n - 1, pos); }
  CEXP u32 kth_min(u32 k) NE { return kth_min_(1, 0, n - 1, k); }
  CEXP u32 kth_max(u32 k) NE { return kth_max_(1, 0, n - 1, k); }
  CEXP u32 frequency(u32 k) NE { return frequency_(1, 0, n - 1, k, k); }
  CEXP u32 frequency(u32 l, u32 r) NE { return frequency_(1, 0, n - 1, l, r); }

 private:
  CEXP void ins_(u32 x, u32 l, u32 r, u32 pos) NE {
    if (l == r) return void(++t[x]);
    if (u32 mid = l + (r - l) / 2; pos <= mid) ins_(x * 2, l, mid, pos);
    else ins_(x * 2 + 1, mid + 1, r, pos);
    t[x] = t[x * 2] + t[x * 2 + 1];
  }
  CEXP void del_(u32 x, u32 l, u32 r, u32 pos) NE {
    if (l == r) return void(--t[x]);
    if (u32 mid = l + (r - l) / 2; pos <= mid) del_(x * 2, l, mid, pos);
    else del_(x * 2 + 1, mid + 1, r, pos);
    t[x] = t[x * 2] + t[x * 2 + 1];
  }
  CEXP u32 kth_min_(u32 x, u32 l, u32 r, u32 k) CNE {
    if (l == r) return l;
    if (u32 mid = l + (r - l) / 2; k <= t[x * 2]) return kth_min_(x * 2, l, mid, k);
    else return kth_min_(x * 2 + 1, mid + 1, r, k - t[x * 2]);
  }
  CEXP u32 kth_max_(u32 x, u32 l, u32 r, u32 k) CNE {
    if (l == r) return l;
    if (u32 mid = l + (r - l) / 2; k <= t[x * 2 + 1]) return kth_max_(x * 2 + 1, mid + 1, r, k);
    else return kth_max_(x * 2, l, mid, k - t[x * 2 + 1]);
  }
  CEXP u32 frequency_(u32 x, u32 l, u32 r, u32 L, u32 R) CNE {
    if (L <= l && R >= r) return t[x];
    u32 mid = l + (r - l) / 2, ret = u32(0);
    if (L <= mid) ret = frequency_(x * 2, l, mid, L, R);
    if (R > mid) ret += frequency_(x * 2 + 1, mid + 1, r, L, R);
    return ret;
  }
};

}  // namespace tifa_libs::ds

#endif