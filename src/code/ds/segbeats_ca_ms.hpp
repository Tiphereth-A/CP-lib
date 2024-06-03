#ifndef TIFALIBS_DS_SEGBEATS_CA_MS
#define TIFALIBS_DS_SEGBEATS_CA_MS

#include "../util/util.hpp"

namespace tifa_libs::ds {

//! 0-based
template <class T, class TT = T>
requires(sizeof(T) <= sizeof(TT))
struct segbeats_ca_ms {
  static CEXP T INF = std::numeric_limits<T>::max() / 2 - 1;

  struct TIFA {
    TT sum = 0;
    T max = 0, min = 0, max2 = -INF, min2 = INF;
    u32 cmax = 1, cmin = 1;
    T add = 0;
  };

  vec<TIFA> v;
  u32 n, lbn;

  CEXP explicit segbeats_ca_ms() {}
  CEXP explicit segbeats_ca_ms(u32 _n) : segbeats_ca_ms(vec<T>(_n)) {}
  CEXP explicit segbeats_ca_ms(vec<T> CR a) { reset(a); }

  CEXP void reset(spn<T> a) {
    if (a.empty()) return n = lbn = 0, v.clear();
    lbn = (u32)std::bit_width(a.size() - 1), n = 1_u32 << lbn, v.resize(2 * n);
    flt_ (u32, i, 0, (u32)a.size()) v[i + n].sum = v[i + n].max = v[i + n].min = a[i];
    for (u32 i = n - 1; i; --i) pushup(i);
  }
  CEXP void chmin(u32 l, u32 r, T x) { update_<1>(l, r, x); }
  CEXP void chmax(u32 l, u32 r, T x) { update_<2>(l, r, x); }
  CEXP void add(u32 l, u32 r, T x) { update_<3>(l, r, x); }
  CEXP void set(u32 l, u32 r, T x) { update_<4>(l, r, x); }
  CEXP T query_min(u32 l, u32 r) { return query_<1>(l, r); }
  CEXP T query_max(u32 l, u32 r) { return query_<2>(l, r); }
  CEXP TT query_sum(u32 l, u32 r) { return query_<3>(l, r); }

 private:
  template <int tp>
  CEXP auto e() {
    if CEXP (tp == 1) return INF;
    if CEXP (tp == 2) return -INF;
    if CEXP (tp == 3) return (TT)0;
  }
  template <int tp>
  CEXP void op(auto& a, TIFA CR b) {
    if CEXP (tp == 1) a = min(a, b.min);
    if CEXP (tp == 2) a = max(a, b.max);
    if CEXP (tp == 3) a += b.sum;
  }
  template <int tp>
  CEXP void apply_(u32 k, T x) {
    if CEXP (tp == 1) chmins_(k, x);
    if CEXP (tp == 2) chmaxs_(k, x);
    if CEXP (tp == 3) pdadd_(k, x);
    if CEXP (tp == 4) chmins_(k, x), chmaxs_(k, x);
  }
  CEXP void chmins_(u32 k, T x) {
    if (v[k].max <= x) return;
    if (v[k].max2 < x) return pdmin_(k, x);
    pushdown(k), chmins_(k * 2, x), chmins_(k * 2 + 1, x), pushup(k);
  }
  CEXP void chmaxs_(u32 k, T x) {
    if (x <= v[k].min) return;
    if (x < v[k].min2) return pdmax_(k, x);
    pushdown(k), chmaxs_(k * 2, x), chmaxs_(k * 2 + 1, x), pushup(k);
  }

  CEXP void pushup(u32 k) {
    TIFA &p = v[k], &l = v[k * 2], &r = v[k * 2 + 1];
    p.sum = l.sum + r.sum;
    if (l.max == r.max) p.max = l.max, p.max2 = max(l.max2, r.max2), p.cmax = l.cmax + r.cmax;
    else {
      bool f = l.max > r.max;
      p.max = f ? l.max : r.max, p.cmax = f ? l.cmax : r.cmax, p.max2 = max(f ? r.max : l.max, f ? l.max2 : r.max2);
    }
    if (l.min == r.min) p.min = l.min, p.min2 = min(l.min2, r.min2), p.cmin = l.cmin + r.cmin;
    else {
      bool f = l.min < r.min;
      p.min = f ? l.min : r.min, p.cmin = f ? l.cmin : r.cmin, p.min2 = min(f ? r.min : l.min, f ? l.min2 : r.min2);
    }
  }
  CEXP void pushdown(u32 k) {
    TIFA& p = v[k];
    if (p.add) pdadd_(k * 2, p.add), pdadd_(k * 2 + 1, p.add), p.add = 0;
    if (p.max < v[k * 2].max) pdmin_(k * 2, p.max);
    if (p.min > v[k * 2].min) pdmax_(k * 2, p.min);
    if (p.max < v[k * 2 + 1].max) pdmin_(k * 2 + 1, p.max);
    if (p.min > v[k * 2 + 1].min) pdmax_(k * 2 + 1, p.min);
  }
  CEXP void pdadd_(u32 k, T x) {
    TIFA& p = v[k];
    if (p.sum += (TT)x << ((int)lbn + std::countl_zero(k) - 31), p.max += x, p.min += x; p.max2 != -INF) p.max2 += x;
    if (p.min2 != INF) p.min2 += x;
    p.add += x;
  }
  void pdmin_(u32 k, T x) {
    TIFA& p = v[k];
    if (p.sum += ((TT)x - p.max) * p.cmax; p.min == p.max) p.min = x;
    if (p.min2 == p.max) p.min2 = x;
    p.max = x;
  }
  void pdmax_(u32 k, T x) {
    TIFA& p = v[k];
    if (p.sum += ((TT)x - p.min) * p.cmin; p.max == p.min) p.max = x;
    if (p.max2 == p.min) p.max2 = x;
    p.min = x;
  }
  template <int tp>
  CEXP void update_(u32 l, u32 r, T x) {
    assert(l <= r);
    if (l == r) return;
    l += n, r += n;
    u32 zl = (u32)std::countr_zero(l), zr = (u32)std::countr_zero(r), zm = min(zl, zr);
    for (u32 i = lbn; i >= 1; i--) {
      if (((l >> i) << i) != l) pushdown(l >> i);
      if (((r >> i) << i) != r) pushdown((r - 1) >> i);
    }
    u32 l2 = l, r2 = r;
    while (l2 < r2) {
      if (l2 & 1) apply_<tp>(l2++, x);
      if (r2 & 1) apply_<tp>(--r2, x);
      l2 /= 2, r2 /= 2;
    }
    fle_ (u32, i, zm + 1, lbn) {
      if (zl < i) pushup(l >> i);
      if (zr < i) pushup((r - 1) >> i);
    }
  }
  template <int tp>
  CEXP auto query_(u32 l, u32 r) {
    if (l == r) return e<tp>();
    l += n, r += n;
    for (u32 zl = (u32)std::countr_zero(l), zr = (u32)std::countr_zero(r), i = lbn, ie = (u32)max(1, (i32)min(zl, zr)); i >= ie; --i) {
      if (zl < i) pushdown(l >> i);
      if (zr < i) pushdown((r - 1) >> i);
    }
    auto ql = e<tp>(), qr = e<tp>();
    while (l < r) {
      if (l & 1) op<tp>(ql, v[l++]);
      if (r & 1) op<tp>(qr, v[--r]);
      l /= 2, r /= 2;
    }
    if CEXP (tp == 1) return min(ql, qr);
    if CEXP (tp == 2) return max(ql, qr);
    if CEXP (tp == 3) return ql + qr;
  }
};

}  // namespace tifa_libs::ds

#endif