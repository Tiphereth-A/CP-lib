#ifndef TIFA_LIBS_DS_PERSISTENT_SEGTREE
#define TIFA_LIBS_DS_PERSISTENT_SEGTREE

#include <cstddef>

#include "../util/util.hpp"


namespace tifa_libs::ds {

class persistent_segtree {
  //!!! initial cnt = 1;
  size_t n, cnt;
  struct YYZ {
    size_t w, ls, rs;
    YYZ(size_t W = 0, size_t LS = 0, size_t RS = 0) : w(W), ls(LS), rs(RS) {}
  };
  vec<YYZ> t;
  vec<size_t> root;

  void pushup(size_t x) {
    t[x].w = 0;
    if (t[x].ls) t[x].w = t[t[x].ls].w;
    if (t[x].rs) t[x].w += t[t[x].rs].w;
  }
  void build(size_t& x, size_t l, size_t r, size_t pos) {
    x = (++cnt);
    if (l == r) {
      if (l == pos) ++t[x].w;
      return;
    }
    size_t mid = l + (r - l) / 2;
    build(t[x].ls, l, mid, pos), build(t[x].rs, mid + 1, r, pos);
    pushup(x);
  }
  void add_(size_t old_x, size_t& x, size_t l, size_t r, size_t pos) {
    t[x = (++cnt)] = t[old_x];
    if (l == r) return void(++t[x].w);
    size_t mid = l + (r - l) / 2;
    if (pos <= mid) add_(t[old_x].ls, t[x].ls, l, mid, pos);
    else add_(t[old_x].rs, t[x].rs, mid + 1, r, pos);
    pushup(x);
  }
  size_t kth_min_(size_t x, size_t y, size_t l, size_t r, size_t k) {
    if (l == r) return l;
    size_t mid = l + (r - l) / 2, kk = t[t[y].ls].w - t[t[x].ls].w;
    if (k <= kk) return kth_min_(t[x].ls, t[y].ls, l, mid, k);
    return kth_min_(t[x].rs, t[y].rs, mid + 1, r, k - kk);
  }
  size_t kth_max_(size_t x, size_t y, size_t l, size_t r, size_t k) {
    if (l == r) return l;
    size_t mid = l + (r - l) / 2, kk = t[t[y].rs].w - t[t[x].rs].w;
    if (k <= kk) return kth_max_(t[x].rs, t[y].rs, mid + 1, r, k);
    return kth_max_(t[x].ls, t[y].ls, l, mid, k - kk);
  }
  size_t frequency_(size_t x, size_t y, size_t l, size_t r, size_t L, size_t R) {
    if (L <= l && R >= r) return t[y].w - t[x].w;
    size_t mid = l + (r - l) / 2, ret = size_t(0);
    if (L <= mid) ret = frequency_(t[x].ls, t[y].rs, l, mid, L, R);
    if (R > mid) ret += frequency_(t[x].rs, t[y].rs, mid + 1, r, L, R);
    return ret;
  }
  size_t kth_min_(size_t y, size_t l, size_t r, size_t k) {
    if (l == r) return l;
    size_t mid = l + (r - l) / 2, kk = t[t[y].ls].w;
    if (k <= kk) return kth_min_(t[y].ls, l, mid, k);
    return kth_min_(t[y].rs, mid + 1, r, k - kk);
  }
  size_t kth_max_(size_t y, size_t l, size_t r, size_t k) {
    if (l == r) return l;
    size_t mid = l + (r - l) / 2, kk = t[t[y].rs].w;
    if (k <= kk) return kth_max_(t[y].rs, mid + 1, r, k);
    return kth_max_(t[y].ls, l, mid, k - kk);
  }
  size_t frequency_(size_t y, size_t l, size_t r, size_t L, size_t R) {
    if (L <= l && R >= r) return t[y].w;
    size_t mid = l + (r - l) / 2, ret = size_t(0);
    if (L <= mid) ret = frequency_(t[y].rs, l, mid, L, R);
    if (R > mid) ret += frequency_(t[y].rs, mid + 1, r, L, R);
    return ret;
  }

 public:
  persistent_segtree(vec<size_t> const& a, size_t N) : n(N), cnt(0), t(a.size() * 24, YYZ()), root(a.size()) {
    build(root[0], 0, n - 1, a[0]);
    for (size_t i = 1; i < a.size(); ++i) add_(root[i - 1], root[i], 0, n - 1, a[i]);
  }
  void add(size_t old_x, size_t x, size_t pos) { add_(root[old_x], root[x], 0, n - 1, pos); }
  size_t kth_min(size_t x, size_t y, size_t k) { return x ? kth_min_(root[x - 1], root[y], 0, n - 1, k) : kth_min_(root[y], 0, n - 1, k); }
  size_t kth_max(size_t x, size_t y, size_t k) { return x ? kth_max_(root[x - 1], root[y], 0, n - 1, k) : kth_max_(root[y], 0, n - 1, k); }
  size_t frequency(size_t x, size_t y, size_t pos) { return x ? frequency_(root[x - 1], root[y], 0, n - 1, pos, pos) : frequency_(root[y], 0, n - 1, pos, pos); }
  size_t frequency(size_t x, size_t y, size_t L, size_t R) { return x ? frequency_(root[x - 1], root[y], 0, n - 1, L, R) : frequency_(root[y], 0, n - 1, L, R); }
};

}  // namespace tifa_libs::ds

#endif