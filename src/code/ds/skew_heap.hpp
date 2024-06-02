#ifndef TIFALIBS_DS_SKEW_HEAP
#define TIFALIBS_DS_SKEW_HEAP

#include "../util/util.hpp"

namespace tifa_libs::ds {

template <class T, class C = std::less<T>>
class skew_heap {
  static CEXP C comp_{};
  struct TIFA {
    T k, lz;
    u32 l, r, idx;
    TIFA() {}
    TIFA(cT_(T) key, u32 i = -1_u32) : k(key), lz(0), l(-1_u32), r(-1_u32), idx(i) {}
  };

  CEXP bool comp(u32 idxl, u32 idxr) const { return comp_(weight(idxl), weight(idxr)); }
  CEXP void pd(u32 idx) {
    if (d[idx].lz == 0) return;
    if (~d[idx].l) d[d[idx].l].lz += d[idx].lz;
    if (~d[idx].r) d[d[idx].r].lz += d[idx].lz;
    d[idx].k += d[idx].lz, d[idx].lz = 0;
  }

 public:
  vec<TIFA> d;

  CEXP T weight(u32 idx) const { return d[idx].k + d[idx].lz; }
  CEXP u32 newheap(cT_(T) key, u32 idx = -1_u32) { return d.emplace_back(key, idx), u32(d.size() - 1); }
  CEXP u32 merge(u32 x, u32 y) {
    if (!~x || !~y) return ~(x ^ y);
    if (!comp(x, y)) swap(x, y);
    return pd(x), swap(d[x].l, d[x].r = merge(d[x].r, y)), x;
  }
  CEXP void apply(u32 x, cT_(T) lz) { d[x].lz += lz, pd(x); }
  CEXP u32 push(u32 x, cT_(T) key, u32 idx = -1_u32) { return merge(x, newheap(key, idx)); }
  CEXP u32 pop(u32 x) { return pd(x), merge(d[x].l, d[x].r); }
};

}  // namespace tifa_libs::ds

#endif