#ifndef TIFALIBS_DS_PERSISTENT_SEGTREE
#define TIFALIBS_DS_PERSISTENT_SEGTREE

#include "../util/alias_others.hpp"

namespace tifa_libs::ds {

class persistent_segtree {
  //! initial cnt = 1;
  u32 n, cnt;
  struct TIFA {
    u32 w, ls, rs;
    CEXP TIFA(u32 W = 0, u32 LS = 0, u32 RS = 0) NE : w(W), ls(LS), rs(RS) {}
  };
  vec<TIFA> t;
  vecu root;

 public:
  CEXP persistent_segtree(spnu a, u32 N) NE : n(N), cnt(0), t(a.size() * 24, TIFA()), root(a.size()) {
    build(root[0], 0, n - 1, a[0]);
    flt_ (u32, i, 1, (u32)a.size()) add_(root[i - 1], root[i], 0, n - 1, a[i]);
  }
  CEXP void add(u32 old_x, u32 x, u32 pos) NE { add_(root[old_x], root[x], 0, n - 1, pos); }
  CEXP u32 kth_min(u32 x, u32 y, u32 k) NE { return x ? kth_min_(root[x - 1], root[y], 0, n - 1, k) : kth_min_(root[y], 0, n - 1, k); }
  CEXP u32 kth_max(u32 x, u32 y, u32 k) NE { return x ? kth_max_(root[x - 1], root[y], 0, n - 1, k) : kth_max_(root[y], 0, n - 1, k); }
  CEXP u32 frequency(u32 x, u32 y, u32 pos) NE { return x ? frequency_(root[x - 1], root[y], 0, n - 1, pos, pos) : frequency_(root[y], 0, n - 1, pos, pos); }
  CEXP u32 frequency(u32 x, u32 y, u32 L, u32 R) NE { return x ? frequency_(root[x - 1], root[y], 0, n - 1, L, R) : frequency_(root[y], 0, n - 1, L, R); }

 private:
  CEXP void pushup(u32 x) NE {
    if (t[x].w = 0; t[x].ls) t[x].w = t[t[x].ls].w;
    if (t[x].rs) t[x].w += t[t[x].rs].w;
  }
  CEXP void build(u32& x, u32 l, u32 r, u32 pos) NE {
    if (x = ++cnt; l == r) {
      if (l == pos) ++t[x].w;
      return;
    }
    u32 mid = l + (r - l) / 2;
    build(t[x].ls, l, mid, pos), build(t[x].rs, mid + 1, r, pos), pushup(x);
  }
  CEXP void add_(u32 old_x, u32& x, u32 l, u32 r, u32 pos) NE {
    if (assert(pos >= l && pos <= r), t[x = (++cnt)] = t[old_x]; l == r) return void(++t[x].w);
    if (u32 mid = l + (r - l) / 2; pos <= mid) add_(t[old_x].ls, t[x].ls, l, mid, pos);
    else add_(t[old_x].rs, t[x].rs, mid + 1, r, pos);
    pushup(x);
  }
  CEXP u32 kth_min_(u32 x, u32 y, u32 l, u32 r, u32 k) NE {
    if (l == r) return l;
    if (u32 mid = l + (r - l) / 2, kk = t[t[y].ls].w - t[t[x].ls].w; k <= kk) return kth_min_(t[x].ls, t[y].ls, l, mid, k);
    else return kth_min_(t[x].rs, t[y].rs, mid + 1, r, k - kk);
  }
  CEXP u32 kth_max_(u32 x, u32 y, u32 l, u32 r, u32 k) NE {
    if (l == r) return l;
    if (u32 mid = l + (r - l) / 2, kk = t[t[y].rs].w - t[t[x].rs].w; k <= kk) return kth_max_(t[x].rs, t[y].rs, mid + 1, r, k);
    else return kth_max_(t[x].ls, t[y].ls, l, mid, k - kk);
  }
  CEXP u32 frequency_(u32 x, u32 y, u32 l, u32 r, u32 L, u32 R) NE {
    if (assert(R >= l && L <= r); L <= l && R >= r) return t[y].w - t[x].w;
    u32 mid = l + (r - l) / 2, ret = u32(0);
    if (L <= mid) ret = frequency_(t[x].ls, t[y].rs, l, mid, L, R);
    if (R > mid) ret += frequency_(t[x].rs, t[y].rs, mid + 1, r, L, R);
    return ret;
  }
  CEXP u32 kth_min_(u32 y, u32 l, u32 r, u32 k) NE {
    if (l == r) return l;
    if (u32 mid = l + (r - l) / 2, kk = t[t[y].ls].w; k <= kk) return kth_min_(t[y].ls, l, mid, k);
    else return kth_min_(t[y].rs, mid + 1, r, k - kk);
  }
  CEXP u32 kth_max_(u32 y, u32 l, u32 r, u32 k) NE {
    if (l == r) return l;
    if (u32 mid = l + (r - l) / 2, kk = t[t[y].rs].w; k <= kk) return kth_max_(t[y].rs, mid + 1, r, k);
    else return kth_max_(t[y].ls, l, mid, k - kk);
  }
  CEXP u32 frequency_(u32 y, u32 l, u32 r, u32 L, u32 R) NE {
    if (assert(R >= l && L <= r); L <= l && R >= r) return t[y].w;
    u32 mid = l + (r - l) / 2, ret = u32(0);
    if (L <= mid) ret = frequency_(t[y].rs, l, mid, L, R);
    if (R > mid) ret += frequency_(t[y].rs, mid + 1, r, L, R);
    return ret;
  }
};

}  // namespace tifa_libs::ds

#endif