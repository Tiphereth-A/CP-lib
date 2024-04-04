#ifndef TIFALIBS_DS_PERSISTENT_SEGTREE
#define TIFALIBS_DS_PERSISTENT_SEGTREE

#include "../util/util.hpp"

namespace tifa_libs::ds {

class persistent_segtree {
  //! initial cnt = 1;
  u32 n, cnt;
  struct YYZ {
    u32 w, ls, rs;
    constexpr YYZ(u32 W = 0, u32 LS = 0, u32 RS = 0) : w(W), ls(LS), rs(RS) {}
  };
  vec<YYZ> t;
  vecu root;

 public:
  constexpr persistent_segtree(vecu const& a, u32 N) : n(N), cnt(0), t(a.size() * 24, YYZ()), root(a.size()) {
    build(root[0], 0, n - 1, a[0]);
    for (u32 i = 1; i < a.size(); ++i) add_(root[i - 1], root[i], 0, n - 1, a[i]);
  }
  constexpr void add(u32 old_x, u32 x, u32 pos) { add_(root[old_x], root[x], 0, n - 1, pos); }
  constexpr u32 kth_min(u32 x, u32 y, u32 k) { return x ? kth_min_(root[x - 1], root[y], 0, n - 1, k) : kth_min_(root[y], 0, n - 1, k); }
  constexpr u32 kth_max(u32 x, u32 y, u32 k) { return x ? kth_max_(root[x - 1], root[y], 0, n - 1, k) : kth_max_(root[y], 0, n - 1, k); }
  constexpr u32 frequency(u32 x, u32 y, u32 pos) { return x ? frequency_(root[x - 1], root[y], 0, n - 1, pos, pos) : frequency_(root[y], 0, n - 1, pos, pos); }
  constexpr u32 frequency(u32 x, u32 y, u32 L, u32 R) { return x ? frequency_(root[x - 1], root[y], 0, n - 1, L, R) : frequency_(root[y], 0, n - 1, L, R); }

 private:
  constexpr void pushup(u32 x) {
    t[x].w = 0;
    if (t[x].ls) t[x].w = t[t[x].ls].w;
    if (t[x].rs) t[x].w += t[t[x].rs].w;
  }
  constexpr void build(u32& x, u32 l, u32 r, u32 pos) {
    x = (++cnt);
    if (l == r) {
      if (l == pos) ++t[x].w;
      return;
    }
    u32 mid = l + (r - l) / 2;
    build(t[x].ls, l, mid, pos), build(t[x].rs, mid + 1, r, pos);
    pushup(x);
  }
  constexpr void add_(u32 old_x, u32& x, u32 l, u32 r, u32 pos) {
    assert(pos >= l && pos <= r);
    t[x = (++cnt)] = t[old_x];
    if (l == r) return void(++t[x].w);
    u32 mid = l + (r - l) / 2;
    if (pos <= mid) add_(t[old_x].ls, t[x].ls, l, mid, pos);
    else add_(t[old_x].rs, t[x].rs, mid + 1, r, pos);
    pushup(x);
  }
  constexpr u32 kth_min_(u32 x, u32 y, u32 l, u32 r, u32 k) {
    if (l == r) return l;
    u32 mid = l + (r - l) / 2, kk = t[t[y].ls].w - t[t[x].ls].w;
    if (k <= kk) return kth_min_(t[x].ls, t[y].ls, l, mid, k);
    return kth_min_(t[x].rs, t[y].rs, mid + 1, r, k - kk);
  }
  constexpr u32 kth_max_(u32 x, u32 y, u32 l, u32 r, u32 k) {
    if (l == r) return l;
    u32 mid = l + (r - l) / 2, kk = t[t[y].rs].w - t[t[x].rs].w;
    if (k <= kk) return kth_max_(t[x].rs, t[y].rs, mid + 1, r, k);
    return kth_max_(t[x].ls, t[y].ls, l, mid, k - kk);
  }
  constexpr u32 frequency_(u32 x, u32 y, u32 l, u32 r, u32 L, u32 R) {
    assert(R >= l && L <= r);
    if (L <= l && R >= r) return t[y].w - t[x].w;
    u32 mid = l + (r - l) / 2, ret = u32(0);
    if (L <= mid) ret = frequency_(t[x].ls, t[y].rs, l, mid, L, R);
    if (R > mid) ret += frequency_(t[x].rs, t[y].rs, mid + 1, r, L, R);
    return ret;
  }
  constexpr u32 kth_min_(u32 y, u32 l, u32 r, u32 k) {
    if (l == r) return l;
    u32 mid = l + (r - l) / 2, kk = t[t[y].ls].w;
    if (k <= kk) return kth_min_(t[y].ls, l, mid, k);
    return kth_min_(t[y].rs, mid + 1, r, k - kk);
  }
  constexpr u32 kth_max_(u32 y, u32 l, u32 r, u32 k) {
    if (l == r) return l;
    u32 mid = l + (r - l) / 2, kk = t[t[y].rs].w;
    if (k <= kk) return kth_max_(t[y].rs, mid + 1, r, k);
    return kth_max_(t[y].ls, l, mid, k - kk);
  }
  constexpr u32 frequency_(u32 y, u32 l, u32 r, u32 L, u32 R) {
    assert(R >= l && L <= r);
    if (L <= l && R >= r) return t[y].w;
    u32 mid = l + (r - l) / 2, ret = u32(0);
    if (L <= mid) ret = frequency_(t[y].rs, l, mid, L, R);
    if (R > mid) ret += frequency_(t[y].rs, mid + 1, r, L, R);
    return ret;
  }
};

}  // namespace tifa_libs::ds

#endif