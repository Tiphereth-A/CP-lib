#ifndef TIFALIBS_DS_SEGBEATS_CA_MSH
#define TIFALIBS_DS_SEGBEATS_CA_MSH

#include "../util/alias_others.hpp"

namespace tifa_libs::ds {

template <class T, class T1 = T>
class segbeats_ca_msh {
  struct TIFA {
    T1 sum;
    T min, min2, cmin, max, max2, cmax, hismax;
  };
  struct NFO {
    T add1, add2, add3;  // add sign of min, max and (no min or max)
    T maxadd1, maxadd2, maxadd3;
  };
  u32 n;
  vec<TIFA> t;
  vec<NFO> tag;
  T INF;

 public:
  CEXPE segbeats_ca_msh(vec<T> CR a) NE : n((u32)a.size()), t(a.size() * 4), tag(a.size() * 4), INF(std::numeric_limits<T>::max()) { build(a, 1, 0, n - 1); }
  CEXPE segbeats_ca_msh(u32 N) NE : n(N), t(N * 4), tag(N * 4), INF(std::numeric_limits<T>::max()) { build(vec<T>(n, 0), 1, 0, n - 1); }

  CEXP void add(u32 x, u32 l, u32 r, u32 L, u32 R, T k) NE {
    if (assert(R >= l && L <= r); L <= l && r <= R) return all_update(x, l, r, k, k, k, k, k, k);
    pushdown(x, l, r);
    u32 mid = l + (r - l) / 2;
    if (L <= mid) add(x * 2, l, mid, L, R, k);
    if (R > mid) add(x * 2 + 1, mid + 1, r, L, R, k);
    pushup(x);
  }
  CEXP void chmax(u32 x, u32 l, u32 r, u32 L, u32 R, T k) NE {
    if (assert(R >= l && L <= r); k <= t[x].min) return;
    if (L <= l && r <= R && k < t[x].min2) return all_update(x, l, r, k - t[x].min, 0, 0, k - t[x].min, 0, 0);
    pushdown(x, l, r);
    u32 mid = l + (r - l) / 2;
    if (L <= mid) chmax(x * 2, l, mid, L, R, k);
    if (R > mid) chmax(x * 2 + 1, mid + 1, r, L, R, k);
    pushup(x);
  }
  CEXP void chmin(u32 x, u32 l, u32 r, u32 L, u32 R, T k) NE {
    if (assert(R >= l && L <= r); k >= t[x].max) return;
    if (L <= l && r <= R && k > t[x].max2) return all_update(x, l, r, 0, k - t[x].max, 0, 0, k - t[x].max, 0);
    pushdown(x, l, r);
    u32 mid = l + (r - l) / 2;
    if (L <= mid) chmin(x * 2, l, mid, L, R, k);
    if (R > mid) chmin(x * 2 + 1, mid + 1, r, L, R, k);
    pushup(x);
  }
  CEXP T1 querys(u32 x, u32 l, u32 r, u32 L, u32 R) NE {
    if (assert(R >= l && L <= r); L <= l && r <= R) return t[x].sum;
    pushdown(x, l, r);
    u32 mid = l + (r - l) / 2;
    T1 ret = 0;
    if (L <= mid) ret = querys(x * 2, l, mid, L, R);
    if (R > mid) ret += querys(x * 2 + 1, mid + 1, r, L, R);
    return ret;
  }
  CEXP T querymax(u32 x, u32 l, u32 r, u32 L, u32 R) NE {
    if (assert(R >= l && L <= r); L <= l && r <= R) return t[x].max;
    pushdown(x, l, r);
    u32 mid = l + (r - l) / 2;
    T ret = -INF;
    if (L <= mid) ret = querymax(x * 2, l, mid, L, R);
    if (R > mid) ret = max(ret, querymax(x * 2 + 1, mid + 1, r, L, R));
    return ret;
  }
  CEXP T queryhismax(u32 x, u32 l, u32 r, u32 L, u32 R) NE {
    if (assert(R >= l && L <= r); L <= l && r <= R) return t[x].hismax;
    pushdown(x, l, r);
    u32 mid = l + (r - l) / 2;
    T ret = -INF;
    if (L <= mid) ret = queryhismax(x * 2, l, mid, L, R);
    if (R > mid) ret = max(ret, queryhismax(x * 2 + 1, mid + 1, r, L, R));
    return ret;
  }

 private:
  CEXP void pushup(u32 x) NE {
    t[x].sum = t[x * 2].sum + t[x * 2 + 1].sum;
    t[x].hismax = max(t[x * 2].hismax, t[x * 2 + 1].hismax);
    if (t[x * 2].min == t[x * 2 + 1].min) {
      t[x].min = t[x * 2].min;
      t[x].min2 = min(t[x * 2].min2, t[x * 2 + 1].min2);
      t[x].cmin = t[x * 2].cmin + t[x * 2 + 1].cmin;
    } else if (t[x * 2].min < t[x * 2 + 1].min) {
      t[x].min = t[x * 2].min;
      t[x].min2 = min(t[x * 2].min2, t[x * 2 + 1].min);
      t[x].cmin = t[x * 2].cmin;
    } else {
      t[x].min = t[x * 2 + 1].min;
      t[x].min2 = min(t[x * 2].min, t[x * 2 + 1].min2);
      t[x].cmin = t[x * 2 + 1].cmin;
    }
    if (t[x * 2].max == t[x * 2 + 1].max) {
      t[x].max = t[x * 2].max;
      t[x].max2 = max(t[x * 2].max2, t[x * 2 + 1].max2);
      t[x].cmax = t[x * 2].cmax + t[x * 2 + 1].cmax;
    } else if (t[x * 2].max > t[x * 2 + 1].max) {
      t[x].max = t[x * 2].max;
      t[x].max2 = max(t[x * 2].max2, t[x * 2 + 1].max);
      t[x].cmax = t[x * 2].cmax;
    } else {
      t[x].max = t[x * 2 + 1].max;
      t[x].max2 = max(t[x * 2].max, t[x * 2 + 1].max2);
      t[x].cmax = t[x * 2 + 1].cmax;
    }
  }
  CEXP void all_update(u32 x, u32 l, u32 r, T add1, T add2, T add3, T maxadd1, T maxadd2, T maxadd3) NE {
    if (t[x].min == t[x].max) {
      if (add1 == add3) add1 = add2;
      else add2 = add1;
      t[x].sum += T1(add1) * t[x].cmin;
    } else t[x].sum += T1(add1) * t[x].cmin + T1(add2) * t[x].cmax + T1(add3) * (T1(r - l + 1) - t[x].cmin - t[x].cmax);
    // t[x].hismax = max(t[x].hismax, t[x].min + maxadd1);
    t[x].hismax = max(t[x].hismax, t[x].max + maxadd2);
    tag[x].maxadd1 = max(tag[x].maxadd1, tag[x].add1 + maxadd1);
    tag[x].maxadd2 = max(tag[x].maxadd2, tag[x].add2 + maxadd2);
    tag[x].maxadd3 = max(tag[x].maxadd3, tag[x].add3 + maxadd3);
    if (t[x].min2 == t[x].max) t[x].min2 += add2;
    else if (t[x].min2 != INF) t[x].min2 += add3;
    if (t[x].max2 == t[x].min) t[x].max2 += add1;
    else if (t[x].max2 != -INF) t[x].max2 += add3;
    t[x].min += add1, t[x].max += add2;
    tag[x].add1 += add1, tag[x].add2 += add2, tag[x].add3 += add3;
  }
  CEXP void pushdown(u32 x, u32 l, u32 r) NE {
    if (tag[x].add1 || tag[x].add2 || tag[x].add2 || tag[x].maxadd2 || tag[x].maxadd2 || tag[x].maxadd2) {
      u32 mid = l + (r - l) / 2;
      T mn = min(t[x * 2].min, t[x * 2 + 1].min), mx = max(t[x * 2].max, t[x * 2 + 1].max);
      if (t[x * 2].min == mn) {
        if (t[x * 2].max == mx) all_update(x * 2, l, mid, tag[x].add1, tag[x].add2, tag[x].add3, tag[x].maxadd1, tag[x].maxadd2, tag[x].maxadd3);
        else all_update(x * 2, l, mid, tag[x].add1, tag[x].add3, tag[x].add3, tag[x].maxadd1, tag[x].maxadd3, tag[x].maxadd3);
      } else if (t[x * 2].max == mx) all_update(x * 2, l, mid, tag[x].add3, tag[x].add2, tag[x].add3, tag[x].maxadd3, tag[x].maxadd2, tag[x].maxadd3);
      else all_update(x * 2, l, mid, tag[x].add3, tag[x].add3, tag[x].add3, tag[x].maxadd3, tag[x].maxadd3, tag[x].maxadd3);
      if (t[x * 2 + 1].min == mn) {
        if (t[x * 2 + 1].max == mx) all_update(x * 2 + 1, mid + 1, r, tag[x].add1, tag[x].add2, tag[x].add3, tag[x].maxadd1, tag[x].maxadd2, tag[x].maxadd3);
        else all_update(x * 2 + 1, mid + 1, r, tag[x].add1, tag[x].add3, tag[x].add3, tag[x].maxadd1, tag[x].maxadd3, tag[x].maxadd3);
      } else if (t[x * 2 + 1].max == mx) all_update(x * 2 + 1, mid + 1, r, tag[x].add3, tag[x].add2, tag[x].add3, tag[x].maxadd3, tag[x].maxadd2, tag[x].maxadd3);
      else all_update(x * 2 + 1, mid + 1, r, tag[x].add3, tag[x].add3, tag[x].add3, tag[x].maxadd3, tag[x].maxadd3, tag[x].maxadd3);
      tag[x] = {0, 0, 0, 0, 0, 0};
    }
  }
  CEXP void build(spn<T> a, u32 x, u32 l, u32 r) NE {
    if (l == r) {
      t[x].sum = t[x].hismax = t[x].min = t[x].max = a[l];
      t[x].min2 = INF;
      t[x].max2 = -INF;
      t[x].cmin = t[x].cmax = 1;
      return;
    }
    u32 mid = l + (r - l) / 2;
    build(a, x * 2, l, mid), build(a, x * 2 + 1, mid + 1, r);
    pushup(x);
  }
};

}  // namespace tifa_libs::ds

#endif