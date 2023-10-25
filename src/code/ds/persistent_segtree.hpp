#ifndef TIFA_LIBS_DS_PERSISTENT_SEGTREE
#define TIFA_LIBS_DS_PERSISTENT_SEGTREE

#include "../util/util.hpp"

namespace tifa_libs::ds {

class persistent_segtree {
  //!!! initial cnt = 1;
  usz n, cnt;
  struct YYZ {
    usz w, ls, rs;
    YYZ(usz W = 0, usz LS = 0, usz RS = 0) : w(W), ls(LS), rs(RS) {}
  };
  vec<YYZ> t;
  vec<usz> root;

  void pushup(usz x) {
    t[x].w = 0;
    if (t[x].ls) t[x].w = t[t[x].ls].w;
    if (t[x].rs) t[x].w += t[t[x].rs].w;
  }
  void build(usz& x, usz l, usz r, usz pos) {
    x = (++cnt);
    if (l == r) {
      if (l == pos) ++t[x].w;
      return;
    }
    usz mid = l + (r - l) / 2;
    build(t[x].ls, l, mid, pos), build(t[x].rs, mid + 1, r, pos);
    pushup(x);
  }
  void add_(usz old_x, usz& x, usz l, usz r, usz pos) {
    assert(pos >= l && pos <= r);
    t[x = (++cnt)] = t[old_x];
    if (l == r) return void(++t[x].w);
    usz mid = l + (r - l) / 2;
    if (pos <= mid) add_(t[old_x].ls, t[x].ls, l, mid, pos);
    else add_(t[old_x].rs, t[x].rs, mid + 1, r, pos);
    pushup(x);
  }
  usz kth_min_(usz x, usz y, usz l, usz r, usz k) {
    if (l == r) return l;
    usz mid = l + (r - l) / 2, kk = t[t[y].ls].w - t[t[x].ls].w;
    if (k <= kk) return kth_min_(t[x].ls, t[y].ls, l, mid, k);
    return kth_min_(t[x].rs, t[y].rs, mid + 1, r, k - kk);
  }
  usz kth_max_(usz x, usz y, usz l, usz r, usz k) {
    if (l == r) return l;
    usz mid = l + (r - l) / 2, kk = t[t[y].rs].w - t[t[x].rs].w;
    if (k <= kk) return kth_max_(t[x].rs, t[y].rs, mid + 1, r, k);
    return kth_max_(t[x].ls, t[y].ls, l, mid, k - kk);
  }
  usz frequency_(usz x, usz y, usz l, usz r, usz L, usz R) {
    assert(R >= l && L <= r);
    if (L <= l && R >= r) return t[y].w - t[x].w;
    usz mid = l + (r - l) / 2, ret = usz(0);
    if (L <= mid) ret = frequency_(t[x].ls, t[y].rs, l, mid, L, R);
    if (R > mid) ret += frequency_(t[x].rs, t[y].rs, mid + 1, r, L, R);
    return ret;
  }
  usz kth_min_(usz y, usz l, usz r, usz k) {
    if (l == r) return l;
    usz mid = l + (r - l) / 2, kk = t[t[y].ls].w;
    if (k <= kk) return kth_min_(t[y].ls, l, mid, k);
    return kth_min_(t[y].rs, mid + 1, r, k - kk);
  }
  usz kth_max_(usz y, usz l, usz r, usz k) {
    if (l == r) return l;
    usz mid = l + (r - l) / 2, kk = t[t[y].rs].w;
    if (k <= kk) return kth_max_(t[y].rs, mid + 1, r, k);
    return kth_max_(t[y].ls, l, mid, k - kk);
  }
  usz frequency_(usz y, usz l, usz r, usz L, usz R) {
    assert(R >= l && L <= r);
    if (L <= l && R >= r) return t[y].w;
    usz mid = l + (r - l) / 2, ret = usz(0);
    if (L <= mid) ret = frequency_(t[y].rs, l, mid, L, R);
    if (R > mid) ret += frequency_(t[y].rs, mid + 1, r, L, R);
    return ret;
  }

 public:
  persistent_segtree(vec<usz> const& a, usz N) : n(N), cnt(0), t(a.size() * 24, YYZ()), root(a.size()) {
    build(root[0], 0, n - 1, a[0]);
    for (usz i = 1; i < a.size(); ++i) add_(root[i - 1], root[i], 0, n - 1, a[i]);
  }
  void add(usz old_x, usz x, usz pos) { add_(root[old_x], root[x], 0, n - 1, pos); }
  usz kth_min(usz x, usz y, usz k) { return x ? kth_min_(root[x - 1], root[y], 0, n - 1, k) : kth_min_(root[y], 0, n - 1, k); }
  usz kth_max(usz x, usz y, usz k) { return x ? kth_max_(root[x - 1], root[y], 0, n - 1, k) : kth_max_(root[y], 0, n - 1, k); }
  usz frequency(usz x, usz y, usz pos) { return x ? frequency_(root[x - 1], root[y], 0, n - 1, pos, pos) : frequency_(root[y], 0, n - 1, pos, pos); }
  usz frequency(usz x, usz y, usz L, usz R) { return x ? frequency_(root[x - 1], root[y], 0, n - 1, L, R) : frequency_(root[y], 0, n - 1, L, R); }
};

}  // namespace tifa_libs::ds

#endif