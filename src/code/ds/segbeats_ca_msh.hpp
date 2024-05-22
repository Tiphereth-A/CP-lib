#ifndef TIFALIBS_DS_SEGBEATS_CA_MSH
#define TIFALIBS_DS_SEGBEATS_CA_MSH

#include "../util/util.hpp"

namespace tifa_libs::ds {

template <class T, class T1 = T>
class segbeats_ca_msh {
  struct TIFA {
    T1 sum;
    T _min, secmin, cntmin;
    T _max, secmax, cntmax, hismax;
  };
  struct NFO {
    T add1, add2, add3;  // add sign of min, max and (no min or max)
    T maxadd1, maxadd2, maxadd3;
  };
  u32 n;
  vec<TIFA> t;
  vec<NFO> sign;
  T INF;

 public:
  explicit CEXP segbeats_ca_msh(vec<T> CR a) : n(a.size()), t(a.size() * 4), sign(a.size() * 4), INF(std::numeric_limits<T>::max()) { build(a, 1, 0, n - 1); }
  explicit CEXP segbeats_ca_msh(u32 N) : n(N), t(N * 4), sign(N * 4), INF(std::numeric_limits<T>::max()) { build(vec<T>(n, 0), 1, 0, n - 1); }

  CEXP void add(u32 x, u32 l, u32 r, u32 L, u32 R, T k) {
    assert(R >= l && L <= r);
    if (L <= l && r <= R) {
      all_update(x, l, r, k, k, k, k, k, k);
      return;
    }
    pushdown(x, l, r);
    u32 mid = l + (r - l) / 2;
    if (L <= mid) add(x * 2, l, mid, L, R, k);
    if (R > mid) add(x * 2 + 1, mid + 1, r, L, R, k);
    pushup(x);
  }
  CEXP void chmax(u32 x, u32 l, u32 r, u32 L, u32 R, T k) {
    assert(R >= l && L <= r);
    if (k <= t[x]._min) return;
    if (L <= l && r <= R && k < t[x].secmin) {
      all_update(x, l, r, k - t[x]._min, 0, 0, k - t[x]._min, 0, 0);
      return;
    }
    pushdown(x, l, r);
    u32 mid = l + (r - l) / 2;
    if (L <= mid) chmax(x * 2, l, mid, L, R, k);
    if (R > mid) chmax(x * 2 + 1, mid + 1, r, L, R, k);
    pushup(x);
  }
  CEXP void chmin(u32 x, u32 l, u32 r, u32 L, u32 R, T k) {
    assert(R >= l && L <= r);
    if (k >= t[x]._max) return;
    if (L <= l && r <= R && k > t[x].secmax) {
      all_update(x, l, r, 0, k - t[x]._max, 0, 0, k - t[x]._max, 0);
      return;
    }
    pushdown(x, l, r);
    u32 mid = l + (r - l) / 2;
    if (L <= mid) chmin(x * 2, l, mid, L, R, k);
    if (R > mid) chmin(x * 2 + 1, mid + 1, r, L, R, k);
    pushup(x);
  }
  CEXP T1 querys(u32 x, u32 l, u32 r, u32 L, u32 R) {
    assert(R >= l && L <= r);
    if (L <= l && r <= R) return t[x].sum;
    pushdown(x, l, r);
    u32 mid = l + (r - l) / 2;
    T1 ret = 0;
    if (L <= mid) ret = querys(x * 2, l, mid, L, R);
    if (R > mid) ret += querys(x * 2 + 1, mid + 1, r, L, R);
    return ret;
  }
  CEXP T querymax(u32 x, u32 l, u32 r, u32 L, u32 R) {
    assert(R >= l && L <= r);
    if (L <= l && r <= R) return t[x]._max;
    pushdown(x, l, r);
    u32 mid = l + (r - l) / 2;
    T ret = -INF;
    if (L <= mid) ret = querymax(x * 2, l, mid, L, R);
    if (R > mid) ret = max(ret, querymax(x * 2 + 1, mid + 1, r, L, R));
    return ret;
  }
  CEXP T queryhismax(u32 x, u32 l, u32 r, u32 L, u32 R) {
    assert(R >= l && L <= r);
    if (L <= l && r <= R) return t[x].hismax;
    pushdown(x, l, r);
    u32 mid = l + (r - l) / 2;
    T ret = -INF;
    if (L <= mid) ret = queryhismax(x * 2, l, mid, L, R);
    if (R > mid) ret = max(ret, queryhismax(x * 2 + 1, mid + 1, r, L, R));
    return ret;
  }

 private:
  CEXP void pushup(u32 x) {
    t[x].sum = t[x * 2].sum + t[x * 2 + 1].sum;
    t[x].hismax = max(t[x * 2].hismax, t[x * 2 + 1].hismax);
    if (t[x * 2]._min == t[x * 2 + 1]._min) {
      t[x]._min = t[x * 2]._min;
      t[x].secmin = min(t[x * 2].secmin, t[x * 2 + 1].secmin);
      t[x].cntmin = t[x * 2].cntmin + t[x * 2 + 1].cntmin;
    } else if (t[x * 2]._min < t[x * 2 + 1]._min) {
      t[x]._min = t[x * 2]._min;
      t[x].secmin = min(t[x * 2].secmin, t[x * 2 + 1]._min);
      t[x].cntmin = t[x * 2].cntmin;
    } else {
      t[x]._min = t[x * 2 + 1]._min;
      t[x].secmin = min(t[x * 2]._min, t[x * 2 + 1].secmin);
      t[x].cntmin = t[x * 2 + 1].cntmin;
    }
    if (t[x * 2]._max == t[x * 2 + 1]._max) {
      t[x]._max = t[x * 2]._max;
      t[x].secmax = max(t[x * 2].secmax, t[x * 2 + 1].secmax);
      t[x].cntmax = t[x * 2].cntmax + t[x * 2 + 1].cntmax;
    } else if (t[x * 2]._max > t[x * 2 + 1]._max) {
      t[x]._max = t[x * 2]._max;
      t[x].secmax = max(t[x * 2].secmax, t[x * 2 + 1]._max);
      t[x].cntmax = t[x * 2].cntmax;
    } else {
      t[x]._max = t[x * 2 + 1]._max;
      t[x].secmax = max(t[x * 2]._max, t[x * 2 + 1].secmax);
      t[x].cntmax = t[x * 2 + 1].cntmax;
    }
  }
  CEXP void all_update(u32 x, u32 l, u32 r, T add1, T add2, T add3, T maxadd1, T maxadd2, T maxadd3) {
    if (t[x]._min == t[x]._max) {
      if (add1 == add3) add1 = add2;
      else add2 = add1;
      t[x].sum += T1(add1) * t[x].cntmin;
    } else t[x].sum += T1(add1) * t[x].cntmin + T1(add2) * t[x].cntmax + T1(add3) * (T1(r - l + 1) - t[x].cntmin - t[x].cntmax);
    // t[x].hismax = max(t[x].hismax, t[x]._min + maxadd1);
    t[x].hismax = max(t[x].hismax, t[x]._max + maxadd2);
    sign[x].maxadd1 = max(sign[x].maxadd1, sign[x].add1 + maxadd1);
    sign[x].maxadd2 = max(sign[x].maxadd2, sign[x].add2 + maxadd2);
    sign[x].maxadd3 = max(sign[x].maxadd3, sign[x].add3 + maxadd3);
    if (t[x].secmin == t[x]._max) t[x].secmin += add2;
    else if (t[x].secmin != INF) t[x].secmin += add3;

    if (t[x].secmax == t[x]._min) t[x].secmax += add1;
    else if (t[x].secmax != -INF) t[x].secmax += add3;

    t[x]._min += add1, t[x]._max += add2;
    sign[x].add1 += add1, sign[x].add2 += add2, sign[x].add3 += add3;
  }
  CEXP void pushdown(u32 x, u32 l, u32 r) {
    if (sign[x].add1 || sign[x].add2 || sign[x].add2 || sign[x].maxadd2 || sign[x].maxadd2 || sign[x].maxadd2) {
      u32 mid = l + (r - l) / 2;
      T _min = min(t[x * 2]._min, t[x * 2 + 1]._min);
      T _max = max(t[x * 2]._max, t[x * 2 + 1]._max);
      if (t[x * 2]._min == _min) {
        if (t[x * 2]._max == _max) all_update(x * 2, l, mid, sign[x].add1, sign[x].add2, sign[x].add3, sign[x].maxadd1, sign[x].maxadd2, sign[x].maxadd3);
        else all_update(x * 2, l, mid, sign[x].add1, sign[x].add3, sign[x].add3, sign[x].maxadd1, sign[x].maxadd3, sign[x].maxadd3);
      } else if (t[x * 2]._max == _max) all_update(x * 2, l, mid, sign[x].add3, sign[x].add2, sign[x].add3, sign[x].maxadd3, sign[x].maxadd2, sign[x].maxadd3);
      else all_update(x * 2, l, mid, sign[x].add3, sign[x].add3, sign[x].add3, sign[x].maxadd3, sign[x].maxadd3, sign[x].maxadd3);

      if (t[x * 2 + 1]._min == _min) {
        if (t[x * 2 + 1]._max == _max) all_update(x * 2 + 1, mid + 1, r, sign[x].add1, sign[x].add2, sign[x].add3, sign[x].maxadd1, sign[x].maxadd2, sign[x].maxadd3);
        else all_update(x * 2 + 1, mid + 1, r, sign[x].add1, sign[x].add3, sign[x].add3, sign[x].maxadd1, sign[x].maxadd3, sign[x].maxadd3);
      } else if (t[x * 2 + 1]._max == _max) all_update(x * 2 + 1, mid + 1, r, sign[x].add3, sign[x].add2, sign[x].add3, sign[x].maxadd3, sign[x].maxadd2, sign[x].maxadd3);
      else all_update(x * 2 + 1, mid + 1, r, sign[x].add3, sign[x].add3, sign[x].add3, sign[x].maxadd3, sign[x].maxadd3, sign[x].maxadd3);

      sign[x] = {0, 0, 0, 0, 0, 0};
    }
  }
  CEXP void build(vec<T> CR a, u32 x, u32 l, u32 r) {
    if (l == r) {
      t[x].hismax = t[x].sum = t[x]._min = t[x]._max = a[l];
      t[x].secmin = INF, t[x].secmax = -INF;
      t[x].cntmin = t[x].cntmax = 1;
      return;
    }
    u32 mid = l + (r - l) / 2;
    build(a, x * 2, l, mid), build(a, x * 2 + 1, mid + 1, r);
    pushup(x);
  }
};

}  // namespace tifa_libs::ds

#endif