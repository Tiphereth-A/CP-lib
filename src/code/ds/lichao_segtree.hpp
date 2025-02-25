#ifndef TIFALIBS_DS_LICHAO_SEGTREE
#define TIFALIBS_DS_LICHAO_SEGTREE

#include "../util/util.hpp"

namespace tifa_libs::ds {

template <class T, T (*op)(T, T)>
class lichao_segtree {
  struct seg {
    u32 id;
    T a, b, l, r;
    CEXP T w(T x) CNE { return a * x + b; }
  };
  u32 sz;
  vec<T> lsh;
  vec<seg> t;

 public:
  CEXPE lichao_segtree(spn<T> LSH) NE : lsh(LSH.begin(), LSH.end()), t(LSH.size() * 4) { sz = (u32)lsh.size(); }

  // $y = ax + b~(x \in [l, r])$
  CEXP void add(T a, T b, T l, T r, u32 id = 1) NE { add(1, 0, sz - 1, u32(lower_bound(lsh, l) - lsh.begin()), u32(lower_bound(lsh, r) - lsh.begin()), {id, a, b, l, r}); }
  T query(T pos) NE { return query(1, 0, sz - 1, pos); }

 private:
  // min: <=   max: >=
  CEXP bool pd(T a, T b) CNE { return op(a, b) == a; }
  CEXP void add(u32 x, u32 l, u32 r, u32 L, u32 R, seg CR k) NE {
    u32 mid = l + (r - l) / 2;
    if (L <= l && R >= r) {
      if (!t[x].id) return void(t[x] = k);
      T tl = t[x].w(lsh[l]), tr = t[x].w(lsh[r]), kl = k.w(lsh[l]), kr = k.w(lsh[r]);
      if (pd(tl, kl) && pd(tr, kr)) return;
      if (!pd(tl, kl) && !pd(tr, kr)) return void(t[x] = k);
      if (T in = (t[x].b - k.b) / (k.a - t[x].a); pd(kl, tl)) {
        if (in <= lsh[mid]) add(x << 1, l, mid, L, R, k);
        else add(x << 1 | 1, mid + 1, r, L, R, t[x]), t[x] = k;
      } else if (in > lsh[mid]) add(x << 1 | 1, mid + 1, r, L, R, k);
      else add(x << 1, l, mid, L, R, t[x]), t[x] = k;
      return;
    }
    if (L <= mid) add(x << 1, l, mid, L, R, k);
    if (R > mid) add(x << 1 | 1, mid + 1, r, L, R, k);
  }
  CEXP T query(u32 x, u32 l, u32 r, T pos) NE {
    T MIN = std::numeric_limits<T>::lowest(), MAX = std::numeric_limits<T>::max();
    T ret = t[x].id ? t[x].w(pos) : (pd(MIN, MAX) ? MAX : MIN);
    if (l == r) return ret;
    if (u32 mid = l + (r - l) / 2; pos <= lsh[mid]) return op(ret, query(x << 1, l, mid, pos));
    else return op(ret, query(x << 1 | 1, mid + 1, r, pos));
  }
};
}  // namespace tifa_libs::ds

#endif